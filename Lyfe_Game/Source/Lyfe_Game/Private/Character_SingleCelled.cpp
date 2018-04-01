// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "StaticMaths.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameMode_Cell.h"

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
		gameMode->SetControlSetting(CONTROLSETTING);
	}

	//Setting health
	maxHealth = 100; //will be calculated through the player's mass later on
	currentHealth = maxHealth;

	//Setting compounds
	SetCompounds();

	_protein.maximum = 100;
	_protein.current = 0;

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

	playerMesh->bGenerateOverlapEvents = true;

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
	float end = cameraAttachmentArm->TargetArmLength + input * CAMERA_ZOOM_FACTOR;

	end = FMath::Clamp(end, CAMERA_ZOOM_MIN_DISTANCE, CAMERA_ZOOM_MAX_DISTANCE);

	cameraAttachmentArm->TargetArmLength =
		FMath::Lerp<float>(start, end, CAMERA_ZOOM_SPEED);
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
	//CO2
	_playerCompounds._CO2.maximum = 10000;
	_playerCompounds._CO2.current = 10;
	_playerCompounds._CO2.balance = -1;

	//Oxygen
	_playerCompounds._O2.maximum = 10000;
	_playerCompounds._O2.current = 10;
	_playerCompounds._O2.balance = -1;

	//Amino Acid
	_playerCompounds._AminoAcid.maximum = 10000;
	_playerCompounds._AminoAcid.current = 10;
	_playerCompounds._AminoAcid.balance = -1;

	//Glucose
	_playerCompounds._Glucose.maximum = 10000;
	_playerCompounds._Glucose.current = 10;
	_playerCompounds._Glucose.balance = -1;

	//Lipid
	_playerCompounds._Lipid.maximum = 10000;
	_playerCompounds._Lipid.current = 10;
	_playerCompounds._Lipid.balance = -1;
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
	AddCompound(_playerCompounds._CO2.balance, ECompound::ECO2);
	AddCompound(_playerCompounds._O2.balance, ECompound::EO2);
	AddCompound(_playerCompounds._AminoAcid.balance, ECompound::EAminoAcid);
	AddCompound(_playerCompounds._Glucose.balance, ECompound::EGlucose);
	AddCompound(_playerCompounds._Lipid.balance, ECompound::ELipid);
}

FString ACharacter_SingleCelled::GetCompoundName(ECompound compound)
{
	return FString();
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

void ACharacter_SingleCelled::AddCompound(int amount, ECompound compound)
{
	//find the right compound to add the amount
	if (compound == ECompound::ECO2)
	{
		//add the amount
		_playerCompounds._CO2.current += amount;

		//check if it's greater than the maximum or smaller than 0 and correct that
		if (_playerCompounds._CO2.current > _playerCompounds._CO2.maximum)
		{
			_playerCompounds._CO2.current = _playerCompounds._CO2.maximum;
		}
		else if (_playerCompounds._CO2.current < 0)
		{
			_playerCompounds._CO2.current = 0;
		}
	}
	else if (compound == ECompound::EO2)
	{
		_playerCompounds._O2.current += amount;

		if (_playerCompounds._O2.current > _playerCompounds._O2.maximum)
		{
			_playerCompounds._O2.current = _playerCompounds._O2.maximum;
		}
		else if (_playerCompounds._O2.current < 0)
		{
			_playerCompounds._O2.current = 0;
		}
	}
	else if (compound == ECompound::EAminoAcid)
	{
		_playerCompounds._AminoAcid.current += amount;

		if (_playerCompounds._AminoAcid.current > _playerCompounds._AminoAcid.maximum)
		{
			_playerCompounds._AminoAcid.current = _playerCompounds._AminoAcid.maximum;
		}
		else if (_playerCompounds._AminoAcid.current < 0)
		{
			_playerCompounds._AminoAcid.current = 0;
		}
	}
	else if (compound == ECompound::EGlucose)
	{
		_playerCompounds._Glucose.current += amount;

		if (_playerCompounds._Glucose.current > _playerCompounds._Glucose.maximum)
		{
			_playerCompounds._Glucose.current = _playerCompounds._Glucose.maximum;
		}
		else if (_playerCompounds._Glucose.current < 0)
		{
			_playerCompounds._Glucose.current = 0;
		}
	}
	else if (compound == ECompound::ELipid)
	{
		_playerCompounds._Lipid.current += amount;

		if (_playerCompounds._Lipid.current > _playerCompounds._Lipid.maximum)
		{
			_playerCompounds._Lipid.current = _playerCompounds._Lipid.maximum;
		}
		else if (_playerCompounds._Lipid.current < 0)
		{
			_playerCompounds._Lipid.current = 0;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at AddCompound()"), *GetCompoundName(compound));
	}
}

int ACharacter_SingleCelled::GetCompound(ECompound compound, bool bMax)
{
	if (bMax)
	{
		if (compound == ECompound::ECO2)
		{
			return _playerCompounds._CO2.maximum;
		}
		else if (compound == ECompound::EO2)
		{
			return _playerCompounds._O2.maximum;
		}
		else if (compound == ECompound::EAminoAcid)
		{
			return _playerCompounds._AminoAcid.maximum;
		}
		else if (compound == ECompound::EGlucose)
		{
			return _playerCompounds._Glucose.maximum;
		}
		else if (compound == ECompound::ELipid)
		{
			return _playerCompounds._Lipid.maximum;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompound()"), *GetCompoundName(compound));
			return 0;
		}
	}
	else
	{
		if (compound == ECompound::ECO2)
		{
			return _playerCompounds._CO2.current;
		}
		else if (compound == ECompound::EO2)
		{
			return _playerCompounds._O2.current;
		}
		else if (compound == ECompound::EAminoAcid)
		{
			return _playerCompounds._AminoAcid.current;
		}
		else if (compound == ECompound::EGlucose)
		{
			return _playerCompounds._Glucose.current;
		}
		else if (compound == ECompound::ELipid)
		{
			return _playerCompounds._Lipid.current;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompound()"), *GetCompoundName(compound));
			return 0;
		}
	}
}

void ACharacter_SingleCelled::AddProtein(int amount)
{
	_protein.current += amount;
	if (_protein.current > _protein.maximum)
	{
		_protein.current = _protein.maximum;
	}
	else if(_protein.current < 0)
	{
		_protein.current = 0;
	}
}

int ACharacter_SingleCelled::GetProtein(bool bMax)
{
	if (bMax)
	{
		return _protein.maximum;
	}
	else
	{
		return _protein.current;
	}
}

int ACharacter_SingleCelled::GetCompoundBalance(ECompound compound)
{
	if (compound == ECompound::ECO2)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._CO2.balance;
		}		
	}
	else if (compound == ECompound::EO2)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._O2.balance;
		}	
	}
	else if (compound == ECompound::EAminoAcid)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._AminoAcid.balance;
		}
	}
	else if (compound == ECompound::EGlucose)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._Glucose.balance;
		}
	}
	else if (compound == ECompound::ELipid)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._Lipid.balance;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompoundBalance()"), *GetCompoundName(compound));
		return 0;
	}
}
