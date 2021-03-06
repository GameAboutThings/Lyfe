// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "StaticMaths.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameMode_Cell.h"
#include "Logging.h"
#include "CompoundStorageComponent_Cell.h"
#include "InputComponent_Cell.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ACharacter_SingleCelled::ACharacter_SingleCelled()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Use a spring ar to give the camera smooth, natural-feeling motion
	USpringArmComponent* cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	cameraArm->SetupAttachment(RootComponent);
	cameraArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	cameraArm->RelativeLocation = FVector(0.f, 0.f, -20.f);
	cameraArm->TargetArmLength = CAMERA_START_DISTANCE;
	cameraArm->bEnableCameraLag = true;
	cameraArm->CameraLagSpeed = 3.f;
	cameraAttachmentArm = cameraArm;

	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraArm, USpringArmComponent::SocketName);

	playerCamera = camera;
	playerCamera->bUsePawnControlRotation = false;

	//Component to let the user know which way he is facing. Rotates in the desired direction
	playerDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerDirection"));
	playerDirection->SetupAttachment(RootComponent, USpringArmComponent::SocketName);

	compoundStorage = CreateDefaultSubobject<UCompoundStorageComponent_Cell>(TEXT("Compound Storage"));

	//set up the input component
	inputComponent = CreateDefaultSubobject<UInputComponent_Cell>(TEXT("InputHandler"));

	//Allow user to control this character
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//bIsMoving = false;
	//bIsRotating = false;
}

// Called when the game starts or when spawned
void ACharacter_SingleCelled::BeginPlay()
{
	Super::BeginPlay();

	SetActorEnableCollision(true);

	//Setting up the control setting (later on done in the gameMode and loaded from saved settings)
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->SetControlSetting(CONTROLSETTING);
	}

	//Setting health
	_metaCell.maxHealth = 100; //will be calculated through the player's mass later on
	_metaCell.currentHealth = _metaCell.maxHealth;

	_metaCell.movementSpeed = 50.f;
	_metaCell.rotationSpeed = 50.f;
	_metaCell.weight = 50.f;

	//set compounds
	//compoundStorage->SetCompounds();

	//Sets the movement variables to neutral.
	_movement = {
				0.f,   //forwardInput
				0.f,   //rightInput
		};

	playerMesh->bGenerateOverlapEvents = true;

	SetPlayerState(EPlayerState::EAlive);
}

// Called every frame
void ACharacter_SingleCelled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_ePlayerState == EPlayerState::EAlive)
	{
		MoveToTargetLocation(DeltaTime);
	}
}

// Called to bind functionality to input
void ACharacter_SingleCelled::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind input axis for right and forward
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_SingleCelled::SetForwardMotion);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_SingleCelled::SetRightMotion);
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACharacter_SingleCelled::OnLeftClick);
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &ACharacter_SingleCelled::OnRightClick);
	PlayerInputComponent->BindAction("InteractGUI", IE_Pressed, this, &ACharacter_SingleCelled::SetInteractGUI);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::MoveToTargetLocation(float DeltaTime)
{
	//If interaction is set to GUI the cell won't move anymore
	if (inputComponent->GetInteractGUI())
		return;
	//Cell will only move forward from it's point of view but ROTATE towards the cursor while doing so resulting in an arch movement.
	//getting player position
	FVector currentLocation = GetActorLocation();

	//moveVector is the vector towards the position the cell should move
	FVector targetLocation = inputComponent->GetTargetPosition();

	FVector directionVector = FVector(targetLocation.X - currentLocation.X, targetLocation.Y - currentLocation.Y, 0.f);

	float distance = sqrt(pow(directionVector.X, 2) + pow(directionVector.Y, 2));

	FRotator movementAngle = directionVector.Rotation();
	float deltaYaw = StaticMaths::FindDeltaAngleDegrees(playerDirection->GetComponentRotation().Yaw, movementAngle.Yaw);

	bool valid = StaticMaths::FindLookAtAngle2D(playerDirection->GetForwardVector(), directionVector, deltaYaw);

	if (!valid)
	{
		deltaYaw = 0.f;
	}

	//keep it inside the bounds
	if (deltaYaw > 360.f)
	{
		deltaYaw -= 360.f;
	}
	else if (deltaYaw < -360.f)
	{
		deltaYaw += 360.f;
	}
	//make sure it only makes rotations between -180� and 180�
	else if (deltaYaw > 180.f)
	{
		deltaYaw = -180.f + (deltaYaw - 180.f);
	}
	else if (deltaYaw < -180.f)
	{
		deltaYaw = 180.f - (deltaYaw + 180.f);
	}

	//for some reason the calculation for deltaYaw returns the negative of what it is supposed to, so....
	deltaYaw = -deltaYaw;


	if (deltaYaw != 0.f && (distance >= ROTATION_THRESHOLD || distance <= -ROTATION_THRESHOLD))
	{

		//debugging
		//DrawDebugString(GetWorld(), FVector(0.f, 0.f, 0.f), _movement.targetLocation.ToString(), 0, FColor::White, 0.01f, false);
		//DrawDebugString(GetWorld(), FVector(10.f, 0.f, 0.f), FString::SanitizeFloat(deltaYaw), 0, FColor::White, 0.01f, false);
		//DrawDebugString(GetWorld(), FVector(-20.f, 0.f, 0.f), directionVector.ToString(), 0, FColor::White, 0.01f, false);



		float maxYawThisFrame = _metaCell.rotationSpeed * DeltaTime;
		if (maxYawThisFrame >= FMath::Abs(deltaYaw))
		{
			//character can reach the rotation within one frame
			playerDirection->SetWorldRotation(movementAngle);
		}
		else
		{
			//can't reach rotation in this frame so the character needs to rotate over several frames
			playerDirection->AddLocalRotation(FRotator(0.0f, FMath::Sign(deltaYaw) *  maxYawThisFrame, 0.0f));
		}
	}

	//set forward movement
	if (distance >= MOVEMENT_THRESHOLD)
	{
		FVector movementDirection = playerDirection->GetForwardVector();
		//FVector currentLocation = GetActorLocation();
		currentLocation.X += movementDirection.X * _metaCell.movementSpeed * DeltaTime;
		currentLocation.Y += movementDirection.Y * _metaCell.movementSpeed * DeltaTime;

		SetActorLocation(currentLocation);
	}
}

void ACharacter_SingleCelled::Die()
{
	SetPlayerState(EPlayerState::EDead);
}

void ACharacter_SingleCelled::Zoom(float input)
{
	float start = cameraAttachmentArm->TargetArmLength;
	float end = cameraAttachmentArm->TargetArmLength + input * CAMERA_ZOOM_FACTOR;

	end = FMath::Clamp(end, CAMERA_ZOOM_MIN_DISTANCE, CAMERA_ZOOM_MAX_DISTANCE);

	cameraAttachmentArm->TargetArmLength =
		FMath::Lerp<float>(start, end, CAMERA_ZOOM_SPEED);
}

void ACharacter_SingleCelled::OnLeftClick()
{
	inputComponent->LeftClick();
}

void ACharacter_SingleCelled::OnRightClick()
{
	inputComponent->RightClick();
}

void ACharacter_SingleCelled::SetInteractGUI()
{
	inputComponent->SetInteractGUI(true);
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::SetForwardMotion(float input)
{
	inputComponent->SetForwardMotion(input);
}

void ACharacter_SingleCelled::SetRightMotion(float input)
{
	inputComponent->SetRightMotion(input);
}

float ACharacter_SingleCelled::GetRotationSpeed()
{
	return _metaCell.rotationSpeed;
}

float ACharacter_SingleCelled::GetMovementSpeed()
{
	return _metaCell.movementSpeed;
}

float ACharacter_SingleCelled::GetMaxHealth()
{
	return _metaCell.maxHealth;
}

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

float ACharacter_SingleCelled::GetWeight()
{
	return _metaCell.weight;
}

float ACharacter_SingleCelled::GetCurrentHealth()
{
	return _metaCell.currentHealth;
}

void ACharacter_SingleCelled::AddHealth(float amount)
{
	_metaCell.currentHealth = _metaCell.currentHealth + amount;

	if (_metaCell.currentHealth <= 0)
	{
		Die();
	}
	else if (_metaCell.currentHealth > _metaCell.maxHealth)
	{
		_metaCell.currentHealth = _metaCell.maxHealth;
	}
}

void ACharacter_SingleCelled::SetPlayerState(EPlayerState newState)
{
	_ePlayerState = newState;
}

EPlayerState ACharacter_SingleCelled::GetPlayerState()
{
	return _ePlayerState;
}

//bool ACharacter_SingleCelled::PlayerIsMoving()
//{
//	return bIsMoving;
//}

UCompoundStorageComponent_Cell * ACharacter_SingleCelled::GetCompoundStorage()
{
	return compoundStorage;
}

class UCameraComponent * ACharacter_SingleCelled::GetPlayerCamera()
{
	return playerCamera;
}

USpringArmComponent * ACharacter_SingleCelled::GetPlayerCameraArm()
{
	return cameraAttachmentArm;
}
