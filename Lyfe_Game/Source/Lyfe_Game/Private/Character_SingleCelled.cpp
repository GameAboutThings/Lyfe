// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACharacter_SingleCelled::ACharacter_SingleCelled()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//----------------This next part is only temporary so the movement and input can be tested

	//Use a spring ar to give the camera smooth, natural-feeling motion
	USpringArmComponent* cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	cameraArm->SetupAttachment(RootComponent);
	cameraArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	cameraArm->RelativeLocation = FVector(0.f, 0.f, -20.f);
	cameraArm->TargetArmLength = CAMERA_DISTANCE;
	cameraArm->bEnableCameraLag = true;
	cameraArm->CameraLagSpeed = 3.f;
	cameraAttachmentArm = cameraArm;

	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//-------------- End of temporary code

}

// Called when the game starts or when spawned
void ACharacter_SingleCelled::BeginPlay()
{
	Super::BeginPlay();

	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("gameMode: %s"), *(GetWorld()->GetAuthGameMode()->GetClass()->GetName()));
		gameMode->SetControlSetting(EControlSettings::EClick);
	}
	//UE_LOG(LogTemp, Warning, TEXT("gameMode: %s"), *(GetWorld()->GetAuthGameMode()->GetClass()->GetName()));

	//Sets the movement variables to neutral.
	_movement = { 0.f, //rotationSpeed || needs to be called from function later on
				0.f,   //movementSpeed || needs to be called from function later on
				0.f,   //forwardInput
				0.f,   //rightInput
				GetActorLocation() //targetLocation
		};

	SetPlayerState(EPlayerState::EAlive);
}

// Called every frame
void ACharacter_SingleCelled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_ePlayerState == EPlayerState::EAlive)
	{
		DetermineTargetLocation();
		MoveToTargetLocation();
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
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::DetermineTargetLocation()
{
	
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		FVector mouseDirection;
		//Check which control setting is activated
		if (gameMode->GetControlSetting() == EControlSettings::EFollowMouse) //Cell follows mouse
		{
			APlayerController* playerController = Cast<APlayerController>(GetController());
			if (playerController != nullptr)
			{
				playerController->DeprojectMousePositionToWorld(_movement.targetLocation, mouseDirection);
				_movement.targetLocation = _movement.targetLocation + (cameraAttachmentArm->TargetArmLength * mouseDirection);
			}
		}
		else if (gameMode->GetControlSetting() == EControlSettings::EWASD) //WASD to move
		{
			//sets up a virtual target location in front of the cell through the input axis
			_movement.targetLocation == FVector(_movement.forwardInput * 100.f, _movement.rightInput * 100.f, 0.f);
		}
		else if (gameMode->GetControlSetting() == EControlSettings::EClick) //Cell moves towards location of mouse click
		{
			//This is handled in the on LeftClick method
		}
	}
}

void ACharacter_SingleCelled::MoveToTargetLocation()
{

	//Cell will only move forward from it's point of view but ROTATE towards the cursor while doing so resulting in an arch movement.
	//getting player position
	FVector currentLocation = GetActorLocation();

	//moveVector is the vector towards the position the cell should move
	FVector directionVector = FVector(_movement.targetLocation.X - currentLocation.X, _movement.targetLocation.Y - currentLocation.Y, 0);


	float distance = sqrt(pow(directionVector.X, 2) + pow(directionVector.Y, 2));

	//the degree it has to rotate towards the target location
	float deg = 0;

	//the forward vector as seen from the cell
	FVector forwardVector = GetActorForwardVector();

	//cosine of the degree the character has to rotate to face in the right direction to move
	forwardVector.Z = 0;
	directionVector.Normalize();
	forwardVector.Normalize();
	deg = FMath::Acos(FVector::DotProduct(forwardVector, directionVector));
	UE_LOG(LogTemp, Warning, TEXT("deg: %d"), deg);
	//still need to check what values this returns. After that I can map it correctly

	//if the cell needs to move: it will also rotate
	if (distance >= MOVEMENT_THRESHOLD)
	{
		if (GetMovementBase())
		{
			GetMovementBase()->AddImpulse(FVector(_movement.movementSpeed, 0.f, 0.f));
		}
	}
	//if the cell doesn't need to move it will only rotate
	else if (deg >= ROTATION_THRESHOLD || deg <= - ROTATION_THRESHOLD)
	{

	}
}

void ACharacter_SingleCelled::Die()
{
	SetPlayerState(EPlayerState::EDead);
}

class UCameraComponent * ACharacter_SingleCelled::GetPlayerCamera()
{
	return playerCamera;
}

void ACharacter_SingleCelled::SetForwardMotion(float input)
{
	_movement.forwardInput = input;
}

void ACharacter_SingleCelled::SetRightMotion(float input)
{
	_movement.rightInput = input;
}

void ACharacter_SingleCelled::Zoom(float input)
{
	//zoom = input;
	float start = cameraAttachmentArm->TargetArmLength;
	float end = cameraAttachmentArm->TargetArmLength + input * ZOOM_FACTOR;

	end = FMath::Clamp(end, ZOOM_MIN_DISTANCE, ZOOM_MAX_DISTANCE);

	cameraAttachmentArm->TargetArmLength =
		FMath::Lerp<float>(start, end, ZOOM_SPEED);
}

void ACharacter_SingleCelled::OnLeftClick()
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode == nullptr)
		return;

	if (gameMode->GetControlSetting() == EControlSettings::EClick)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{
			FVector mouseDirection;
			playerController->DeprojectMousePositionToWorld(_movement.targetLocation, mouseDirection);
			_movement.targetLocation = _movement.targetLocation + (cameraAttachmentArm->TargetArmLength * mouseDirection);
			//UE_LOG(LogTemp, Warning, TEXT("click:  %d | %d | %d"), _movement.targetLocation.X, _movement.targetLocation.Y, _movement.targetLocation.Z);
			//UE_LOG(LogTemp, Warning, TEXT("Player: %d | %d | %d"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
			DrawDebugPoint(GetWorld(), _movement.targetLocation, 10, FColor::Red, true, 0.0f);
			//SetActorLocation(_movement.targetLocation);
		}
	}
}

void ACharacter_SingleCelled::OnRightClick()
{
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

float ACharacter_SingleCelled::GetRotationSpeed()
{
	return _movement.rotationSpeed;
}

float ACharacter_SingleCelled::GetMovementSpeed()
{
	return _movement.movementSpeed;
}

float ACharacter_SingleCelled::GetMaxHealth()
{
	return maxHealth;
}

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

float ACharacter_SingleCelled::GetWeight()
{
	return weight;
}

float ACharacter_SingleCelled::GetCurrentHealth()
{
	return currentHealth;
}

void ACharacter_SingleCelled::AddHealth(float amount)
{
	currentHealth = currentHealth + amount;

	if (currentHealth <= 0)
	{
		Die();
	}
	else if (currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
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

bool ACharacter_SingleCelled::PlayerIsMoving()
{
	return bIsMoving;
}
