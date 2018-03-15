// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "StaticMaths.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"

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
	cameraArm->TargetArmLength = CAMERA_DISTANCE;
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

	//Allow user to control this character
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	bIsMoving = false;
	bIsRotating = false;

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
		gameMode->SetControlSetting(EControlSettings::EFollowMouse);
	}

	//Setting health
	maxHealth = 100; //will be calculated through the player's mass later on
	currentHealth = maxHealth;

	//Setting compounds
	SetCompounds();

	_DNA.maximum = 100;
	_DNA.current = 0;

	//Sets the movement variables to neutral.
	_movement = { 50.f, //rotationSpeed || needs to be called from function later on
				50.f,   //movementSpeed || needs to be called from function later on
				0.f,   //forwardInput
				0.f,   //rightInput
				GetActorLocation(), //targetLocation
				GetActorLocation() //targetLocationPrev
		};

	//make it so the cell looks up at the beginning;
	_movement.targetLocation += playerDirection->GetForwardVector();

	SetPlayerState(EPlayerState::EAlive);
}

// Called every frame
void ACharacter_SingleCelled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_ePlayerState == EPlayerState::EAlive)
	{
		EnforceCompoundBalance();
		DetermineTargetLocation();
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
	PlayerInputComponent->BindAction("InteractGUI", IE_Pressed, this, &ACharacter_SingleCelled::SetInteractGUITrue);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::DetermineTargetLocation()
{
	_movement.targetLocationPrev = _movement.targetLocation;
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
			//This is handled in the Binding methods |||||||| for test reason not anymore

			_movement.targetLocation.X = (_movement.forwardInput * 1000.f) + GetActorLocation().X; //+ (_movement.targetLocationPrev.X / 100.f);
			_movement.targetLocation.Y = (_movement.rightInput * 1000.f) + GetActorLocation().Y; // + (_movement.targetLocationPrev.Y / 100.f);
		}
		else if (gameMode->GetControlSetting() == EControlSettings::EClick) //Cell moves towards location of mouse click
		{
			//This is handled in the on LeftClick method
		}
		
	}

	if (_movement.targetLocation.Z != 0)
	{
		_movement.targetLocation.Z = 0;
	}
}

void ACharacter_SingleCelled::MoveToTargetLocation(float DeltaTime)
{
	//If interaction is set to GUI the cell won't move anymore
	if (bInteractGUI)
		return;
	//Cell will only move forward from it's point of view but ROTATE towards the cursor while doing so resulting in an arch movement.
	//getting player position
	FVector currentLocation = GetActorLocation();

	//moveVector is the vector towards the position the cell should move
	FVector directionVector = FVector(_movement.targetLocation.X - currentLocation.X, _movement.targetLocation.Y - currentLocation.Y, 0.f);

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
	//make sure it only makes rotations between -180° and 180°
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



		float maxYawThisFrame = _movement.rotationSpeed * DeltaTime;
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
		currentLocation.X += movementDirection.X * _movement.movementSpeed * DeltaTime;
		currentLocation.Y += movementDirection.Y * _movement.movementSpeed * DeltaTime;

		SetActorLocation(currentLocation);
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

void ACharacter_SingleCelled::Zoom(float input)
{
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
		}
	}

	//return to the normal game
	bInteractGUI = false;
}

void ACharacter_SingleCelled::OnRightClick()
{
}

void ACharacter_SingleCelled::SetCompounds()
{
	//carbon
	_playerCompounds._carbon.maximum = 10000;
	_playerCompounds._carbon.current = 10000;
	_playerCompounds._carbon.balance = -1;

	//oxygen
	_playerCompounds._oxygen.maximum = 10000;
	_playerCompounds._oxygen.current = 10000;
	_playerCompounds._oxygen.balance = -1;

	//nitrogen
	_playerCompounds._nitrogen.maximum = 10000;
	_playerCompounds._nitrogen.current = 10000;
	_playerCompounds._nitrogen.balance = -1;

	//phosphor
	_playerCompounds._phosphor.maximum = 10000;
	_playerCompounds._phosphor.current = 10000;
	_playerCompounds._phosphor.balance = -1;

	//sulfur
	_playerCompounds._sulfur.maximum = 10000;
	_playerCompounds._sulfur.current = 10000;
	_playerCompounds._sulfur.balance = -1;
}

void ACharacter_SingleCelled::SetInteractGUI(bool bGUI)
{
	bInteractGUI = bGUI;
}

void ACharacter_SingleCelled::SetInteractGUITrue()
{
	SetInteractGUI(true);
}

void ACharacter_SingleCelled::EnforceCompoundBalance()
{
	AddCompound(_playerCompounds._carbon.balance, "carbon");
	AddCompound(_playerCompounds._carbon.balance, "nitrogen");
	AddCompound(_playerCompounds._carbon.balance, "oxygen");
	AddCompound(_playerCompounds._carbon.balance, "phosphor");
	AddCompound(_playerCompounds._carbon.balance, "sulfur");
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::SetForwardMotion(float input)
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		if (gameMode->GetControlSetting() == EControlSettings::EWASD)
		{
			_movement.forwardInput =  FMath::Clamp(input, -1.f, 1.f) * 1.f;
		}
	}
}

void ACharacter_SingleCelled::SetRightMotion(float input)
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		if (gameMode->GetControlSetting() == EControlSettings::EWASD)
		{
			_movement.rightInput =  FMath::Clamp(input, -1.f, 1.f) * 1.f;
		}
	}
}

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

void ACharacter_SingleCelled::AddCompound(int amount, FString compound)
{
	//find the right compound to add the amount
	if (compound.ToLower().Equals("carbon"))
	{
		//add the amount
		_playerCompounds._carbon.current += amount;

		//check if it's greater than the maximum or smaller than 0 and correct that
		if (_playerCompounds._carbon.current > _playerCompounds._carbon.maximum)
		{
			_playerCompounds._carbon.current = _playerCompounds._carbon.maximum;
		}
		else if (_playerCompounds._carbon.current < 0)
		{
			_playerCompounds._carbon.current = 0;
		}
	}
	else if (compound.ToLower().Equals("oxygen"))
	{
		_playerCompounds._oxygen.current += amount;

		if (_playerCompounds._oxygen.current > _playerCompounds._oxygen.maximum)
		{
			_playerCompounds._oxygen.current = _playerCompounds._oxygen.maximum;
		}
		else if (_playerCompounds._oxygen.current < 0)
		{
			_playerCompounds._oxygen.current = 0;
		}
	}
	else if (compound.ToLower().Equals("nitrogen"))
	{
		_playerCompounds._nitrogen.current += amount;

		if (_playerCompounds._nitrogen.current > _playerCompounds._nitrogen.maximum)
		{
			_playerCompounds._nitrogen.current = _playerCompounds._nitrogen.maximum;
		}
		else if (_playerCompounds._nitrogen.current < 0)
		{
			_playerCompounds._nitrogen.current = 0;
		}
	}
	else if (compound.ToLower().Equals("sulfur"))
	{
		_playerCompounds._sulfur.current += amount;

		if (_playerCompounds._sulfur.current > _playerCompounds._sulfur.maximum)
		{
			_playerCompounds._sulfur.current = _playerCompounds._sulfur.maximum;
		}
		else if (_playerCompounds._sulfur.current < 0)
		{
			_playerCompounds._sulfur.current = 0;
		}
	}
	else if (compound.ToLower().Equals("phosphor"))
	{
		_playerCompounds._phosphor.current += amount;

		if (_playerCompounds._phosphor.current > _playerCompounds._phosphor.maximum)
		{
			_playerCompounds._phosphor.current = _playerCompounds._phosphor.maximum;
		}
		else if (_playerCompounds._phosphor.current < 0)
		{
			_playerCompounds._phosphor.current = 0;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at AddCompound()"), *compound);
	}
}

int ACharacter_SingleCelled::GetCompound(FString compound, bool bMax)
{
	if (bMax)
	{
		if (compound.ToLower().Equals("carbon"))
		{
			return _playerCompounds._carbon.maximum;
		}
		else if (compound.ToLower().Equals("oxygen"))
		{
			return _playerCompounds._oxygen.maximum;
		}
		else if (compound.ToLower().Equals("nitrogen"))
		{
			return _playerCompounds._nitrogen.maximum;
		}
		else if (compound.ToLower().Equals("sulfur"))
		{
			return _playerCompounds._sulfur.maximum;
		}
		else if (compound.ToLower().Equals("phosphor"))
		{
			return _playerCompounds._phosphor.maximum;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompound()"), *compound);
			return 0;
		}
	}
	else
	{
		if (compound.ToLower().Equals("carbon"))
		{
			return _playerCompounds._carbon.current;
		}
		else if (compound.ToLower().Equals("oxygen"))
		{
			return _playerCompounds._oxygen.current;
		}
		else if (compound.ToLower().Equals("nitrogen"))
		{
			return _playerCompounds._nitrogen.current;
		}
		else if (compound.ToLower().Equals("sulfur"))
		{
			return _playerCompounds._sulfur.current;
		}
		else if (compound.ToLower().Equals("phosphor"))
		{
			return _playerCompounds._phosphor.current;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompound()"), *compound);
			return 0;
		}
	}
}

void ACharacter_SingleCelled::AddDNA(int amount)
{
	_DNA.current += amount;
	if (_DNA.current > _DNA.maximum)
	{
		_DNA.current = _DNA.maximum;
	}
	else if(_DNA.current < 0)
	{
		_DNA.current = 0;
	}
}

int ACharacter_SingleCelled::GetDNA(bool bMax)
{
	if (bMax)
	{
		return _DNA.maximum;
	}
	else
	{
		return _DNA.current;
	}
}

int ACharacter_SingleCelled::GetCompoundBalance(FString compound)
{
	if (compound.ToLower().Equals("carbon"))
	{
		if (GetCompound("carbon", false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._carbon.balance;
		}		
	}
	else if (compound.ToLower().Equals("oxygen"))
	{
		if (GetCompound("oxygen", false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._oxygen.balance;
		}	
	}
	else if (compound.ToLower().Equals("nitrogen"))
	{
		if (GetCompound("nitrogen", false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._nitrogen.balance;
		}
	}
	else if (compound.ToLower().Equals("sulfur"))
	{
		if (GetCompound("sulfur", false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._sulfur.balance;
		}
	}
	else if (compound.ToLower().Equals("phosphor"))
	{
		if (GetCompound("phosphor", false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._phosphor.balance;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompoundBalance()"), *compound);
		return 0;
	}
}
