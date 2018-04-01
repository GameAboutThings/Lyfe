// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume_Cell.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "StaticMaths.h"
#include "GameMode_Cell.h"
#include "Logging.h"


// Sets default values
ASpawnVolume_Cell::ASpawnVolume_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create the bounds for the spawn volume
	volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	RootComponent = Cast<USceneComponent>(volume);
}

// Called when the game starts or when spawned
void ASpawnVolume_Cell::BeginPlay()
{
	Super::BeginPlay();
	SpawnTick();
}

// Called every frame
void ASpawnVolume_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// PRIVATE ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ASpawnVolume_Cell::SpawnTick()
{
	//First of all set the volume back on the player
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		this->SetActorLocation(controller->GetActorLocation());

		Spawn();

		controller->GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume_Cell::SpawnTick, SURROUNDINGS_DELTA_TIME, false);
	}
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ASpawnVolume_Cell::Spawn()
{
	if (_spawnableObjects.passive != NULL && _spawnableObjects.compoundCloud != NULL) //add all other objects here that are needed
	{
		UWorld* const world = GetWorld();
		AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(world->GetAuthGameMode());
		if (world != nullptr && gameMode != nullptr)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			FVector spawnLocation = GetRandomPointWithinBounds();
			FRotator spawnRotation;

			//pick a random object to spawn
			int obj = StaticMaths::RR(0, 2);
			switch (obj)
			{
			//passive
			case 0:
				if (gameMode->GetPlayerSurroundings(ESpawnable::EPassive) >= SURROUNDINGS_MAX_PASSIVE)
					return;
				spawnRotation.Yaw = FMath::FRand() * 360.f;
				spawnRotation.Pitch = FMath::FRand() * 360.f;
				spawnRotation.Roll = FMath::FRand() * 360.f;
				world->SpawnActor<APassiveObject_Cell>(_spawnableObjects.passive, spawnLocation, spawnRotation, spawnParams);
				gameMode->AddPlayerSurroundings(ESpawnable::EPassive, 1);
				break;
			//compound cloud
			case 1:
				if (gameMode->GetPlayerSurroundings(ESpawnable::ECloud) >= SURROUNDINGS_MAX_CLOUD)
					return;
				spawnRotation.Yaw = 0.f;
				spawnRotation.Pitch = 0.f;
				spawnRotation.Roll = 0.f;
				world->SpawnActor<ACompoundCloud_Cell>(_spawnableObjects.compoundCloud, spawnLocation, spawnRotation, spawnParams);
				gameMode->AddPlayerSurroundings(ESpawnable::ECloud, 1);
				break;
			//cell
			case 2:
				if (gameMode->GetPlayerSurroundings(ESpawnable::ECell) >= SURROUNDINGS_MAX_CELL)
					return;
				break;
			default:
				break;
			}
		}
	}
}

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// PUBLIC ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
FVector ASpawnVolume_Cell::GetRandomPointWithinBounds()
{
	FVector spawnPosition = FVector(0.f);
	FVector innerExtent = volume->Bounds.BoxExtent;

	// top/bottom (true) or left/right (false)
	if (StaticMaths::RandomBool() == 1)
	{
		// set x position randomly
		spawnPosition.X = StaticMaths::RR(-innerExtent.X, innerExtent.X);

		//spawn on top or bottom
		if (StaticMaths::RandomBool() == 1)
		{
			spawnPosition.Y = innerExtent.Y;
		}
		else
		{
			spawnPosition.Y = -innerExtent.Y;
		}
	}
	else
	{
		// set x position randomly
		spawnPosition.Y = StaticMaths::RR(-innerExtent.Y, innerExtent.Y);

		//spawn on top or bottom
		if (StaticMaths::RandomBool() == 1)
		{
			spawnPosition.X = innerExtent.X;
		}
		else
		{
			spawnPosition.X = -innerExtent.X;
		}
	}

	spawnPosition = spawnPosition + this->GetActorLocation();
	
	return spawnPosition;
}

