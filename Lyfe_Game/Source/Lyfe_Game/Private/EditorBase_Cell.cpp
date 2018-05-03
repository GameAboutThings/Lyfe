// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorBase_Cell.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "CellEditor_NodeComponent.h"
#include "CellEditor_ArrowComponent.h"


// Sets default values
AEditorBase_Cell::AEditorBase_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the base node for this cell
	baseNode = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("BaseNode"));
	RootComponent = baseNode;
	baseNode->SetRelativeLocation(FVector(0, 0, 0));
	baseNode->PostConstructor(ENodeType::EBase, EPosition::EBase);

	//Use a spring arm to give the camera smooth, natural-feeling motion
	USpringArmComponent* cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	cameraArm->SetupAttachment(RootComponent);
	cameraArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	cameraArm->RelativeLocation = FVector(0.f, 0.f, 0.f);
	cameraArm->TargetArmLength = CAMERA_START_DISTANCE;
	cameraArm->bEnableCameraLag = true;
	cameraArm->CameraLagSpeed = 3.f;
	cameraAttachmentArm = cameraArm;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraArm, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;

	//Allow user to control this character
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AEditorBase_Cell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEditorBase_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void AEditorBase_Cell::GenerateBodyMesh()
{
	TArray<FVector> vertices;
	TArray<int> indices;
	TArray<FVector> normals;

	//start with the base node and calculate the
	int radiusTemp = baseNode->GetRadius();
	FVector centerOffsetTemp = baseNode->GetRelativeLocation();

	uint_8 latBands = 20;
	uint_8 longBands = 20;

	//generating all the vertices
	for(uint_8 latNumber = 0; latNumber <= latBands; latNumber ++)
	{
		float theta = latNumber * FMath::pi / longBands;
		float sinTheta = FMath::Sin(theta);
		float cosTheta = FMath::Cos(theta);

		for(uint_8 longNumber = 0; longNumber <= longBands; longNumber++)
		{
			float phi = longNumber * 2 * FMath::pi / longBands;
			float sinPhi = FMath::Sin(phi);
			float cosPhi = FMath::Cos(phi);

			normals.Add(FVector(
				cosPhi * sinTheta,
				cosTheta,
				sinPhi * sinTheta
			) + centerOffsetTemp
			);
			vertices.Add(normals[i] * radiusTemp);
		}
	}

	//generating indices
	for(uint_8 latNumber = 0; latNumber < latBands; latNumber++)
	{
		for(uint_8 longNumber = 0; longNumber < longBands; longNumber++)
		{
			uint_8 first = (latNumber * (longBands + 1)) + longNumber;
			uint_8 second = first + longBands + 1;

			indices.Add(first);
			indices.Add(second);
			indices.Add(first + 1);

			indices.Add(second);
			indices.Add(second + 1);
			indices.Add(first + 1);
		}
	}

	//After the base node continue with its children
	//Offset when adding to the index buffer is always the length of the vertex buffer when starting a new sphere
	//This iteration over children has to be done 4x
	TArray<EPosition> pos = baseNode->GetChildrenPositions();
	for(uint_8 i = 0; i < pos.Num; i++)
	{
		UCellEditor_NodeComponent* curNode = baseNode->GetChild(pos[i]);
		centerOffsetTemp = curNode->GetRelativeLocation();
		radiusTemp = curNode->GetRadius();
	}



	/** This function is called to generate the mesh every time it changes therefore I have to first check if I already generated a body mesh before
	 * that I can now modify or have to generate a completly new one.
	 * Currently planned method would be to delete the old mesh and create a new one since I can't update indices but only vertices.
	 * Also it is qicker to just delete the mesh and replace it than checking all vertices and only moving the ones needed evertime you sculpt something.
	 * Deleting the mesh will be called shortly before replacing it as to make the transition look a lot smoother.
	*/
	if(bodyMesh != nullptr)
	{
		bodyMesh->UnregisterComponent();
	}

	bodyMesh->CreateMeshSection_LinearColor(0, vertices, indices, normals, uv0, vertexColors, tangents, true);
	/*mesh->SetMobility(EComponentMobility::Movable);
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mesh->SetCollisionProfileName("OverlapAll");
	SetActorEnableCollision(true);
	//mesh->bUseComplexAsSimpleCollision = true;
	//mesh->SetSimulatePhysics(false);
	//mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mesh->bGenerateOverlapEvents = true;
	mesh->SetCollisionConvexMeshes({ vertices });
	mesh->ContainsPhysicsTriMeshData(false);
	//mesh->UpdateMeshSection_LinearColor(0, vertices, normals, uv0, vertexColors, tangents);*/
}