// Fill out your copyright notice in the Description page of Project Settings.

#include "CompoundCloud_Cell.h"


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
	CreateTriangle();
}

void ACompoundCloud_Cell::PostLoad()
{
	Super::PostLoad();
	CreateTriangle();
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
void ACompoundCloud_Cell::CreateTriangle()
{
	//vertex buffer
	TArray<FVector> vertices;
	//vertices.Add(FVector(0, 0, 0));
	//vertices.Add(FVector(0, 100, 0));
	//vertices.Add(FVector(0, 0, 100));
	//vertices.Add(FVector(0, 100, 100));
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(100, 0, 0));
	vertices.Add(FVector(0, 100, 0));
	vertices.Add(FVector(0, 0, 100));
	vertices.Add(FVector(100, 100, 0));
	vertices.Add(FVector(0, 100, 100));
	vertices.Add(FVector(100, 0, 100));
	vertices.Add(FVector(100, 100, 100));

	//index buffer
	TArray<int32> triangles;
	triangles.Add(0);
	triangles.Add(1);
	triangles.Add(2);
	triangles.Add(1);
	triangles.Add(2);
	triangles.Add(4);

	triangles.Add(3);
	triangles.Add(5);
	triangles.Add(6);
	triangles.Add(5);
	triangles.Add(6);
	triangles.Add(7);

	triangles.Add(1);
	triangles.Add(4);
	triangles.Add(6);
	triangles.Add(4);
	triangles.Add(6);
	triangles.Add(7);

	triangles.Add(2);
	triangles.Add(4);
	triangles.Add(7);
	triangles.Add(2);
	triangles.Add(5);
	triangles.Add(7);

	triangles.Add(0);
	triangles.Add(2);
	triangles.Add(5);
	triangles.Add(0);
	triangles.Add(3);
	triangles.Add(5);

	triangles.Add(0);
	triangles.Add(1);
	triangles.Add(6);
	triangles.Add(0);
	triangles.Add(6);
	triangles.Add(3);

	//normals on every vertex
	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 1, 0));

	// ?????????????????????
	TArray<FVector2D> uv0;
	uv0.Add(FVector2D(0, 0));
	uv0.Add(FVector2D(10, 0));
	uv0.Add(FVector2D(0, 10));

	uv0.Add(FVector2D(0, 0));
	uv0.Add(FVector2D(10, 0));
	uv0.Add(FVector2D(0, 10));

	// ?????????????????????????????
	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, -1, 0));

	//The colors applied to every vertex and blended on the surfaces
	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
	vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
	vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
	vertexColors.Add(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));

	mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uv0, vertexColors, tangents, true);

	//Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}
  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

