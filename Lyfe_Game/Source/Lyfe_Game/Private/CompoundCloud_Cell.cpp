// Fill out your copyright notice in the Description page of Project Settings.

#include "CompoundCloud_Cell.h"
#include "StaticMaths.h"
#include "Logging.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "GameMode_Cell.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "StaticMaths.h"


// Sets default values
ACompoundCloud_Cell::ACompoundCloud_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	
	mesh->bUseAsyncCooking = true;

	//mesh->OnComponentBeginOverlap.AddDynamic(this, &ACompoundCloud_Cell::BeginOverlap);
	//mesh->OnComponentEndOverlap.AddDynamic(this, &ACompoundCloud_Cell::EndOverlap);

}

// Called when the game starts or when spawned
void ACompoundCloud_Cell::BeginPlay()
{
	Super::BeginPlay();
	value = StaticMaths::RR(7000.f, 13000.f);

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

	if (value == 0 || value == NULL)
	{
		value = StaticMaths::RR(7000.f, 13000.f);
	}

	float modifier = value / 10000.f;

	FMeshBounds bounds = {
		StaticMaths::RR(-10.f, 10.f) * modifier,
		StaticMaths::RR(40.f, 60.f) * modifier,
		StaticMaths::RR(90.f, 110.f) * modifier,
		StaticMaths::RR(140.f, 160.f) * modifier,
		StaticMaths::RR(190.f, 210.f) * modifier,
	};

	CreateCloudMesh(bounds);

	type = ECompound(rand()%5);
}

void ACompoundCloud_Cell::PostLoad()
{
	Super::PostLoad();

	if (value == 0 || value == NULL)
	{
		value = StaticMaths::RR(7000.f, 13000.f);
	}

	float modifier = value / 10000.f;

	FMeshBounds bounds = {
		StaticMaths::RR(-10.f, 10.f) * modifier,
		StaticMaths::RR(40.f, 60.f) * modifier,
		StaticMaths::RR(90.f, 110.f) * modifier,
		StaticMaths::RR(140.f, 160.f) * modifier,
		StaticMaths::RR(190.f, 210.f) * modifier,
	};

	CreateCloudMesh(bounds);

	type = ECompound(rand() % 5);
}

// Called every frame
void ACompoundCloud_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bBeingConsumed)
	{
		ReshapeMeshOnConsumption();
		if (value <= 0.f)
		{
			CloudFinishConsumption();
		}
	}
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
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 1, 0));

	//// ?????????????????????
	TArray<FVector2D> uv0;
	//uv0.Add(FVector2D(0, 0));
	//uv0.Add(FVector2D(10, 0));
	//uv0.Add(FVector2D(0, 10));

	//uv0.Add(FVector2D(0, 0));
	//uv0.Add(FVector2D(10, 0));
	//uv0.Add(FVector2D(0, 10));

	//// ?????????????????????????????
	TArray<FProcMeshTangent> tangents;
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));

	////The colors applied to every vertex and blended on the surfaces
	TArray<FLinearColor> vertexColors;
	//vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
	//vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
	//vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));

	mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uv0, vertexColors, tangents, true);

	//Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
	mesh->bUseComplexAsSimpleCollision = false;
	//mesh->SetSimulatePhysics(true);
}

void ACompoundCloud_Cell::CreateCloudMesh(FMeshBounds _b)
{
	//vertex buffer
	//TArray<FVector> vertices;
	//Front
	vertices.Add(FVector(_b.one, -_b.one, -_b.one));//0
	vertices.Add(FVector(_b.one, _b.zero, -_b.one));
	vertices.Add(FVector(_b.one, _b.one, -_b.one));
	vertices.Add(FVector(StaticMaths::RR(_b.one, _b.three), StaticMaths::RR(-_b.three,-_b.one), _b.zero));
	vertices.Add(FVector(StaticMaths::RR(_b.two, _b.four), _b.zero, _b.zero));
	vertices.Add(FVector(StaticMaths::RR(_b.one, _b.three), StaticMaths::RR(_b.one, _b.three), _b.zero));//5
	vertices.Add(FVector(_b.one, -_b.one, _b.one));
	vertices.Add(FVector(_b.one, _b.zero, _b.one));
	vertices.Add(FVector(_b.one, _b.one, _b.one));

	//Left
	//2
	vertices.Add(FVector(_b.zero, _b.one, -_b.one));
	vertices.Add(FVector(-_b.one, _b.one, -_b.one)); //10
	//5
	vertices.Add(FVector(_b.zero, StaticMaths::RR(_b.two, _b.four), _b.zero));
	vertices.Add(FVector(StaticMaths::RR(-_b.three, -_b.one), StaticMaths::RR(_b.one, _b.three), _b.zero));
	//8
	vertices.Add(FVector(_b.zero, _b.one, _b.one));
	vertices.Add(FVector(-_b.one, _b.one, _b.one));

	//Back
	//10
	vertices.Add(FVector(-_b.one, _b.zero, -_b.one)); //15
	vertices.Add(FVector(-_b.one, -_b.one, -_b.one));
	//12
	vertices.Add(FVector(StaticMaths::RR(-_b.four, -_b.two), _b.zero, _b.zero));
	vertices.Add(FVector(StaticMaths::RR(-_b.three, -_b.one), StaticMaths::RR(-_b.three, -_b.one), _b.zero));
	//14
	vertices.Add(FVector(-_b.one, _b.zero, _b.one));
	vertices.Add(FVector(-_b.one, -_b.one, _b.one));//20

	//Left
	//16
	vertices.Add(FVector(_b.zero, -_b.one, -_b.one));
	//0
	//18
	vertices.Add(FVector(_b.zero, StaticMaths::RR(-_b.four, -_b.two), _b.zero));
	//3
	//20
	vertices.Add(FVector(_b.zero, -_b.one, _b.one));
	//6

	//Bottom
	//16
	//15
	//10
	//21
	vertices.Add(FVector(_b.zero, _b.zero, -_b.one));
	//9
	//0
	//1
	//2

	//Top
	//6
	//7
	//8
	//23
	vertices.Add(FVector(_b.zero, _b.zero, _b.one)); //25
	//13
	//20
	//19
	//14


	//index buffer
	//+++++ Front
	//Lower Left
	indices.Add(3);
	indices.Add(1);
	indices.Add(0);
	indices.Add(1);
	indices.Add(3);
	indices.Add(4);
	//Lower Right
	indices.Add(4);
	indices.Add(2);
	indices.Add(1);
	indices.Add(2);
	indices.Add(4);
	indices.Add(5);
	//Upper Left
	indices.Add(6);
	indices.Add(4);
	indices.Add(3);
	indices.Add(4);
	indices.Add(6);
	indices.Add(7);
	//Upper Right
	indices.Add(7);
	indices.Add(5);
	indices.Add(4);
	indices.Add(5);
	indices.Add(7);
	indices.Add(8);

	//+++++ Right
	//Lower Left
	indices.Add(5);
	indices.Add(9);
	indices.Add(2);
	indices.Add(9);
	indices.Add(5);
	indices.Add(11);
	//Lower Right
	indices.Add(11);
	indices.Add(10);
	indices.Add(9);
	indices.Add(10);
	indices.Add(11);
	indices.Add(12);
	//Upper Left
	indices.Add(8);
	indices.Add(11);
	indices.Add(5);
	indices.Add(11);
	indices.Add(8);
	indices.Add(13);
	//Upper Right
	indices.Add(13);
	indices.Add(12);
	indices.Add(11);
	indices.Add(12);
	indices.Add(13);
	indices.Add(14);

	//+++++ Back
	//Lower Left
	indices.Add(12);
	indices.Add(15);
	indices.Add(10);
	indices.Add(15);
	indices.Add(12);
	indices.Add(17);
	//LowerRight
	indices.Add(17);
	indices.Add(16);
	indices.Add(15);
	indices.Add(16);
	indices.Add(17);
	indices.Add(18);
	//Upper Left
	indices.Add(14);
	indices.Add(17);
	indices.Add(12);
	indices.Add(17);
	indices.Add(14);
	indices.Add(19);
	//Upper Right
	indices.Add(19);
	indices.Add(18);
	indices.Add(17);
	indices.Add(18);
	indices.Add(19);
	indices.Add(20);

	//+++++ Left
	//Lower Left
	indices.Add(18);
	indices.Add(21);
	indices.Add(16);
	indices.Add(21);
	indices.Add(18);
	indices.Add(22);
	//Lower Right
	indices.Add(22);
	indices.Add(0);
	indices.Add(21);
	indices.Add(0);
	indices.Add(22);
	indices.Add(3);
	//Upper Left
	indices.Add(20);
	indices.Add(22);
	indices.Add(18);
	indices.Add(22);
	indices.Add(20);
	indices.Add(23);
	//Upper Right
	indices.Add(23);
	indices.Add(3);
	indices.Add(22);
	indices.Add(3);
	indices.Add(23);
	indices.Add(6);

	//+++++ Bottom
	//Lower Left
	indices.Add(21);
	indices.Add(15);
	indices.Add(16);
	indices.Add(15);
	indices.Add(21);
	indices.Add(24);
	//Lower Right
	indices.Add(24);
	indices.Add(10);
	indices.Add(15);
	indices.Add(10);
	indices.Add(24);
	indices.Add(9);
	//Upper Left
	indices.Add(0);
	indices.Add(24);
	indices.Add(21);
	indices.Add(24);
	indices.Add(0);
	indices.Add(1);
	//Upper Right
	indices.Add(1);
	indices.Add(9);
	indices.Add(24);
	indices.Add(9);
	indices.Add(1);
	indices.Add(2);

	//+++++ Top
	//Lower Left
	indices.Add(23);
	indices.Add(7);
	indices.Add(6);
	indices.Add(7);
	indices.Add(23);
	indices.Add(25);
	//Lower Right
	indices.Add(25);
	indices.Add(8);
	indices.Add(7);
	indices.Add(8);
	indices.Add(25);
	indices.Add(13);
	//Upper Left
	indices.Add(20);
	indices.Add(25);
	indices.Add(23);
	indices.Add(25);
	indices.Add(20);
	indices.Add(19);
	//Upper Right
	indices.Add(19);
	indices.Add(13);
	indices.Add(25);
	indices.Add(13);
	indices.Add(19);
	indices.Add(14);


	TArray<FVector> normals;
	for (int i = 0; i < vertices.Num(); i++)
	{
		normals.Add(vertices[i] / vertices[i].Size());
	}
	

	//// ?????????????????????
	TArray<FVector2D> uv0;

	//// ?????????????????????????????
	TArray<FProcMeshTangent> tangents;

	////The colors applied to every vertex and blended on the surfaces
	TArray<FLinearColor> vertexColors;

	mesh->CreateMeshSection_LinearColor(0, vertices, indices, normals, uv0, vertexColors, tangents, true);
	mesh->SetMobility(EComponentMobility::Movable);
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mesh->SetCollisionProfileName("OverlapAll");
	SetActorEnableCollision(true);
	//mesh->bUseComplexAsSimpleCollision = true;
	//mesh->SetSimulatePhysics(false);
	//mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mesh->bGenerateOverlapEvents = true;
	mesh->SetCollisionConvexMeshes({ vertices });
	mesh->ContainsPhysicsTriMeshData(false);
	//mesh->UpdateMeshSection_LinearColor(0, vertices, normals, uv0, vertexColors, tangents);
}
void ACompoundCloud_Cell::ReshapeMeshOnConsumption()
{
	bool moveCenter = false;
	int moveCenterIndex = 0;
	FVector moveCenterDirection = FVector();

	if (consumingCell != nullptr)
	{

	}
	if (consumingPlayer != nullptr)
	{
		FVector location = consumingPlayer->GetActorLocation();
		FVector2D relativePlayerPosition = StaticMaths::ThreeDTo2D(StaticMaths::WorldToLocal(this, location), EPlane::E_XY);
		FVector2D vertex = FVector2D();
		for (int i = 0; i < vertices.Num(); i++)
		{
			vertex = StaticMaths::ThreeDTo2D(vertices[i], EPlane::E_XY);

			//vector from the player to the vertex, so basically the vector along which the vertex is moved
			FVector2D distanceVector = vertex - relativePlayerPosition;

			//distance between player and vertex
			float distance = FMath::Abs(StaticMaths::Distance2D(distanceVector, FVector2D(0.f, 0.f)));

			float degree = 0;
			
			if (distance <= CLOUD_MESH_VERTEX_DISTANCE_THRESHOLD )//|| bPlayerBetweenCenterAndVertex) //and the vertex and player are in roughly the same direction from the center
																//if distance between vertex and player exceeds threshold 
																//or if the player is between the center and the vertex
			{
				FVector2D newVertex;
				newVertex.X = vertices[i].X;
				newVertex.Y = vertices[i].Y;


				degree = 0;

				if (StaticMaths::FindLookAtAngle2D(consumingPlayer->GetActorForwardVector(),
					consumingPlayer->GetActorLocation() - this->GetActorLocation(), degree))
				{

					if (degree <= CLOUD_PLAYERROTATION_THRESHOLD)
					{
						//Move vertex away from player

						//normalize the vector from the player to the vertex
						distanceVector = distanceVector / distance;

						newVertex.X += distanceVector.X * CLOUD_MESH_VERTEX_DELTA_MOVEMENT;
						newVertex.Y += distanceVector.Y * CLOUD_MESH_VERTEX_DELTA_MOVEMENT;
					}
				}
				//Move vertex inward

				//correct the previous calculations so you can't enlarge the cloud
				float n = vertices[i].Size2D();
				newVertex.X -= (vertices[i] / n).X * CLOUD_MESH_VERTEX_DELTA_MOVEMENT;
				newVertex.Y -= (vertices[i] / n).Y * CLOUD_MESH_VERTEX_DELTA_MOVEMENT;

				vertices[i].X = newVertex.X;
				vertices[i].Y = newVertex.Y;

				//consume some of the cloud
				value -= CLOUD_CONSUMPTION_RATE;
				consumingPlayer->AddCompound(CLOUD_CONSUMPTION_RATE, type);

				if(vertices[i].X == 0 && vertices[i].Y == 0)
				{
					if(!moveCenter)
						moveCenterIndex = i;
					
					moveCenter = true;

					//move all following meshes
					moveCenterDirection = StaticMaths::Normalized(this->GetActorLocation() - consumingPlayer->GetActorLocation()) * CLOUD_MESH_CENTER_CELTA_MOVEMENT;

					vertices[i] = vertices[i] + moveCenterDirection;
				}

			}
		}

		if(moveCenter)
		{
			//move all meshes until the index is reached
			for(int i = 0; i < moveCenterIndex; i++)
			{
				vertices[i] = vertices[i] + moveCenterDirection;
			}
		}
	}

	//move center
	this->SetActorLocation(this->GetActorLocation() + moveCenterDirection);

	mesh->UpdateMeshSection_LinearColor(0, vertices, vertices, {}, {}, {});
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
			bBeingConsumed = true;
			consumingPlayer = controller;
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
			bBeingConsumed = false;
			consumingPlayer = nullptr;
		}


		//If a cell is on the compound cloud
	}
}

ECompound ACompoundCloud_Cell::GetType()
{
	return type;
}

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

