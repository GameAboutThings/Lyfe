// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"
#include "Stage_Meta_SingleCelled.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ACharacter_SingleCelled::ACharacter_SingleCelled()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacter_SingleCelled::BeginPlay()
{
	Super::BeginPlay();
	
	//This next part is only temporary so the movement and input can be tested

	//Set sphere as root of this character
	//reacts to physics
	//USphereComponent* sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	//RootComponent = sphereComponent;
	//sphereComponent->InitSphereRadius(40.f);
	//sphereComponent->SetCollisionProfileName(TEXT("CELL_PLAYER"));

	////create and position mesh so sphere is visible
	//UStaticMeshComponent* sphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	//sphereVisual->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> sphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	//if (sphereVisualAsset.Succeeded())
	//{
	//	sphereVisual->SetStaticMesh(sphereVisualAsset.Object);
	//	sphereVisual->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	//	sphereVisual->SetWorldScale3D(FVector(0.8f));
	//}

	SetPlayerState(EPlayerState::EAlive);
}

// Called every frame
void ACharacter_SingleCelled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FollowCourser();
}

// Called to bind functionality to input
void ACharacter_SingleCelled::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ACharacter_SingleCelled::FollowCourser()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController != nullptr)
	{
		float x = 0;
		float y = 0;
		FVector mousePosition = FVector(0, 0, 0);

		//getting courser position on relation to world
		playerController->GetMousePosition(x, y);
		FVector screenPos = FVector(x, y, 0);
		playerController->DeprojectMousePositionToWorld(screenPos, mousePosition);

		//getting player position
		FVector currentPosition = GetActorLocation();

		//determining distance
		FVector toMouse = FVector(mousePosition.X - currentPosition.X, mousePosition.Y - currentPosition.Y, 0);
		float distance = sqrt(pow(toMouse.X, 2) + pow(toMouse.Y, 2));

		//how far to rotate
		float deg = 0;

		if (distance >= MOVEMENT_THRESHOLD)
		{

		}
		else if (deg >= ROTATION_THRESHOLD)
		{

		}
	}
}

void ACharacter_SingleCelled::Die()
{
	SetPlayerState(EPlayerState::EDead);
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
