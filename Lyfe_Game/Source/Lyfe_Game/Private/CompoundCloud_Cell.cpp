// Fill out your copyright notice in the Description page of Project Settings.

#include "CompoundCloud_Cell.h"
#include "StaticMaths.h"
#include "Logging.h"
#include "Character_SingleCelled.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "StaticMaths.h"
#include "CompoundStorageComponent_Cell.h"
#include <string>
#include <math.h>
#include "Compound_ParticleComponent_Cell.h"


// Sets default values
ACompoundCloud_Cell::ACompoundCloud_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	uint8 particleCount = StaticMaths::RR(CLOUD_PARTICLE_MIN, CLOUD_PARTICLE_MAX);

	value = particleCount;
	type = ECompound(rand() % 5);

	// +++++ second idea for distribution of particle systems +++++

	std::string center = "CenterSystem";
	UCompound_ParticleComponent_Cell* temp = CreateDefaultSubobject<UCompound_ParticleComponent_Cell>(FName(center.c_str()));
	particles.Add(temp);
	RootComponent = temp;

	for (uint8 i = 0; i < 100; i++)
	{
		for (int j = 0; j < pow(i, 2); j++)
		{
			//define the name for the current particle system
			//ParticleSystem_<circleNum>_<Num>_<randomSeed>
			std::string name = "ParticleSystem_";
			name.append({ static_cast<char>((i + 1)) });
			name.append({ "_" });
			name.append({ static_cast<char>(j + 1) });
			name.append({ "_" });
			name.append({ static_cast<char>(j + i) });

			//create the particle system with the newly defined name
			UCompound_ParticleComponent_Cell* temp = CreateDefaultSubobject<UCompound_ParticleComponent_Cell>(name.c_str());
			particles.Add(temp);

			temp->SetupAttachment(RootComponent);


			//set up random location within a circle
			double a = (((double)rand() / (RAND_MAX)) + 1) * 2 * PI;
			double r = (CLOUD_RADIUS_STEPS * (i + 1)) * sqrt(((double)rand() / (RAND_MAX)) + 1);

			double x = r * cos(a);
			double y = r * sin(a);

			FVector location = FVector(x, y, 0);

			temp->SetRelativeLocation(location);

			//finally: check if number of elements in array is particle count
			//if so, stop this loop
			if (particleCount - 1 == particles.Num())
			{
				break;
				i = 100;
				j = pow(i, 2);
			}
		}
		if (particleCount - 1 == particles.Num())
		{
			break;
			i = 100;
		}
	}

}

// Called when the game starts or when spawned
void ACompoundCloud_Cell::BeginPlay()
{
	Super::BeginPlay();

	//First of all set the volume back on the player
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		controller->GetWorldTimerManager().SetTimer(despawnTimer, this, &ACompoundCloud_Cell::DespawnTick, 5.f, false);
	}

}

void ACompoundCloud_Cell::PostActorCreated()
{
	Super::PostActorCreated();

	//CreateCloudMesh();
}

void ACompoundCloud_Cell::PostLoad()
{
	Super::PostLoad();

	//CreateCloudMesh();
	type = ECompound(rand() % 5);
}

// Called every frame
void ACompoundCloud_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/* ------------------------------------------------------------------------------------------------- */

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ACompoundCloud_Cell::CreateCube()
{
	//vertex buffer
	TArray<FVector> vertices;
	vertices.Add(FVector(-50, -50, -50));
	vertices.Add(FVector(50, -50, -50));
	vertices.Add(FVector(-50, 50, -50));
	vertices.Add(FVector(-50, -50, 50));
	vertices.Add(FVector(50, 50, -50));
	vertices.Add(FVector(-50, 50, 50));
	vertices.Add(FVector(50, -50, 50));
	vertices.Add(FVector(50, 50, 50));

	//index buffer
	TArray<int32> triangles;
	triangles.Add(0);
	triangles.Add(1);
	triangles.Add(2);
	triangles.Add(4);
	triangles.Add(2);
	triangles.Add(1);

	triangles.Add(3);
	triangles.Add(5);
	triangles.Add(6);
	triangles.Add(7);
	triangles.Add(6);
	triangles.Add(5);

	triangles.Add(1);
	triangles.Add(6);
	triangles.Add(4);
	triangles.Add(7);
	triangles.Add(4);
	triangles.Add(6);

	triangles.Add(4);
	triangles.Add(7);
	triangles.Add(2);
	triangles.Add(5);
	triangles.Add(2);
	triangles.Add(7);

	triangles.Add(2);
	triangles.Add(5);
	triangles.Add(0);
	triangles.Add(3);
	triangles.Add(0);
	triangles.Add(5);

	triangles.Add(1);
	triangles.Add(0);
	triangles.Add(6);
	triangles.Add(3);
	triangles.Add(6);
	triangles.Add(0);

	//normals on every vertex
	TArray<FVector> normals;

	//// ?????????????????????
	TArray<FVector2D> uv0;

	//// ?????????????????????????????
	TArray<FProcMeshTangent> tangents;

	////The colors applied to every vertex and blended on the surfaces
	TArray<FLinearColor> vertexColors;

	//mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uv0, vertexColors, tangents, true);

	//Enable collision data
	//mesh->ContainsPhysicsTriMeshData(true);
	//mesh->bUseComplexAsSimpleCollision = false;
	//mesh->SetSimulatePhysics(true);
}


void ACompoundCloud_Cell::CloudFinishConsumption()
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->AddPlayerSurroundings(ESpawnable::ECloud, -1);
		//mesh->SetVisibility(false);
		this->Destroy();
	}
	else
	{
		Logging::Log("ERROR in CloudFinishConsumption: GameMode could not be referenced ", true);
	}
}

void ACompoundCloud_Cell::DespawnTick()
{
	//First of all set the volume back on the player
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		//check distance to player
		controller->GetActorLocation();
		this->GetActorLocation();

		if (StaticMaths::Distance2D(controller->GetActorLocation(),
			this->GetActorLocation()) >= SURROUNDINGS_DESPAWN_DISTANCE)
		{
			this->Destroy();
		}


		controller->GetWorldTimerManager().SetTimer(despawnTimer, this, &ACompoundCloud_Cell::DespawnTick, 5.f, false);
	}
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ACompoundCloud_Cell::BeginOverlap(AActor* otherActor)
{
	if ((otherActor != nullptr) && (otherActor != this))
	{
		//If the player is on the compound cloud
		ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(otherActor);
		if (controller != nullptr)
		{

		}

		//If a cell is on the compound cloud
	}
}

void ACompoundCloud_Cell::EndOverlap(AActor* otherActor)
{
	if ((otherActor != nullptr) && (otherActor != this))
	{
		//If the player is on the compound cloud
		ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(otherActor);
		if (controller != nullptr)
		{

		}


		//If a cell is on the compound cloud
	}
}



  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ECompound ACompoundCloud_Cell::GetType()
{
	return type;
}

TArray<FVector> ACompoundCloud_Cell::GetVertices()
{
	return TArray<FVector>();
}

TArray<int32> ACompoundCloud_Cell::GetIndices()
{
	return TArray<int32>();
}

UProceduralMeshComponent * ACompoundCloud_Cell::GetMesh()
{
	return nullptr;
}

void ACompoundCloud_Cell::AddValue(int amount)
{
	value += amount;

	if (value <= 0.f)
	{
		CloudFinishConsumption();
	}
}

TArray<UCompound_ParticleComponent_Cell*> ACompoundCloud_Cell::GetParticleComponents()
{
	return particles;
}
