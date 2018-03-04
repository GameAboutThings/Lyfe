// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"
#include "Stage_Meta_SingleCelled.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameMode_Cell.h"


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

	_movement = { 0, 0, 0, 0, FVector(0, 0, 0)};

	SetPlayerState(EPlayerState::EAlive);
}

// Called every frame
void ACharacter_SingleCelled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_ePlayerState == EPlayerState::EAlive)
	{
		FollowCourser();
	}
}

// Called to bind functionality to input
void ACharacter_SingleCelled::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind input axis for right and forward
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_SingleCelled::SetForwardMotion);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_SingleCelled::SetRightMotion);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::DetermineTargetLocation()
{
	//Get GameMode
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		//Check which control setting is activated
		if (gameMode->GetControlSetting() == EControlSettings::EFollowMouse)
		{
			APlayerController* playerController = Cast<APlayerController>(GetController());
			if (playerController != nullptr)
			{
				float x = 0;
				float y = 0;

				//getting courser position in relation to world
				playerController->GetMousePosition(x, y);
				FVector screenPos = FVector(x, y, 0);
				playerController->DeprojectMousePositionToWorld(screenPos, _movement.targetLocation);
			}
		}
		else if (gameMode->GetControlSetting() == EControlSettings::EWASD)
		{
			_movement.targetLocation == FVector(_movement.forwardInput * 100.f, _movement.rightInput * 100.f, 0.f);
		}

		//Cell will only move forward from it's point of view but ROTATE towards the cursor while doing so resulting in an arch movement.
		//getting player position
		FVector currentPosition = GetActorLocation();

		//determining distance
		FVector toMouse = FVector(_movement.targetLocation.X - currentPosition.X, _movement.targetLocation.Y - currentPosition.Y, 0);
		float distance = sqrt(pow(toMouse.X, 2) + pow(toMouse.Y, 2));

		float deg = 0;

		//if the cell needs to move: it will also rotate
		if (distance >= MOVEMENT_THRESHOLD)
		{
			GetMovementBase()->AddImpulse(FVector(_movement.movementSpeed, 0.f, 0.f));
		}
		//if the cell doesn't need to move it will only rotate
		else if (deg >= ROTATION_THRESHOLD)
		{

		}
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
