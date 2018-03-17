// Fill out your copyright notice in the Description page of Project Settings.

#include "CompoundCloud_Cell.h"
#include "StaticMaths.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ACompoundCloud_Cell::ACompoundCloud_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	
	mesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void ACompoundCloud_Cell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACompoundCloud_Cell::PostActorCreated()
{
	Super::PostActorCreated();
	//CreateCube();
	CreateCloudMesh();
}

void ACompoundCloud_Cell::PostLoad()
{
	Super::PostLoad();
	//CreateCube();
	CreateCloudMesh();
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
	mesh->SetSimulatePhysics(true);
}

void ACompoundCloud_Cell::CreateCloudMesh()
{
	//vertex buffer
	TArray<FVector> vertices;
	//Front
	vertices.Add(FVector(50.f, -50.f, -50.f));//0
	vertices.Add(FVector(50.f, 0.f, -50.f));
	vertices.Add(FVector(50.f, 50.f, -50.f));
	vertices.Add(FVector(StaticMaths::RR(50.f, 150.f), StaticMaths::RR(-150.f,-50.f), 0.f));
	vertices.Add(FVector(StaticMaths::RR(100.f, 200.f), 0.f, 0.f));
	vertices.Add(FVector(StaticMaths::RR(50.f, 150.f), StaticMaths::RR(50.f, 150.f), 0.f));//5
	vertices.Add(FVector(50.f, -50.f, 50.f));
	vertices.Add(FVector(50.f, 0.f, 50.f));
	vertices.Add(FVector(50.f, 50.f, 50.f));

	//Left
	//2
	vertices.Add(FVector(0.f, 50.f, -50.f));
	vertices.Add(FVector(-50.f, 50.f, -50.f)); //10
	//5
	vertices.Add(FVector(0.f, StaticMaths::RR(100.f, 200.f), 0.f));
	vertices.Add(FVector(StaticMaths::RR(-150.f, -50.f), StaticMaths::RR(50.f, 150.f), 0.f));
	//8
	vertices.Add(FVector(0.f, 50.f, 50.f));
	vertices.Add(FVector(-50.f, 50.f, 50.f));

	//Back
	//10
	vertices.Add(FVector(-50.f, 0.f, -50.f)); //15
	vertices.Add(FVector(-50.f, -50.f, -50.f));
	//12
	vertices.Add(FVector(StaticMaths::RR(-200.f, -100.f), 0.f, 0.f));
	vertices.Add(FVector(StaticMaths::RR(-150.f, -50.f), StaticMaths::RR(-150.f, -50.f), 0.f));
	//14
	vertices.Add(FVector(-50.f, 0.f, 50.f));
	vertices.Add(FVector(-50.f, -50.f, 50.f));//20

	//Left
	//16
	vertices.Add(FVector(0.f, -50.f, -50.f));
	//0
	//18
	vertices.Add(FVector(0.f, StaticMaths::RR(-200.f, -100.f), 0.f));
	//3
	//20
	vertices.Add(FVector(0.f, -50.f, 50.f));
	//6

	//Bottom
	//16
	//15
	//10
	//21
	vertices.Add(FVector(0.f, 0.f, -50.f));
	//9
	//0
	//1
	//2

	//Top
	//6
	//7
	//8
	//23
	vertices.Add(FVector(0.f, 0.f, 50.f)); //25
	//13
	//20
	//19
	//14


	//index buffer
	TArray<int32> indices;
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

	//Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
	mesh->bUseComplexAsSimpleCollision = false;
	mesh->SetSimulatePhysics(true);
	//mesh->SetVisibility(false);
}
  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

