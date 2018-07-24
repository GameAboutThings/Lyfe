// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorBase_Cell.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "CellEditor_NodeComponent.h"
#include "CellEditor_ArrowComponent.h"
#include "StaticMaths.h"
#include "ProceduralMeshComponent.h"
#include "Meta_CellEditor.h"


// Sets default values
AEditorBase_Cell::AEditorBase_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	idCounter = 0;

	//Create the base node for this cell
	baseNode = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("BaseNode"));
	RootComponent = baseNode;
	baseNode->SetRelativeLocation(FVector(0, 0, 0));
	baseNode->PostConstructor(ENodeType::EBase, EPosition::EBase);
	baseNode->SetEditorBase(this);

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
	idCounter = 0;
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
	FVector centerOffsetTemp = baseNode->GetRelativeTransform().GetLocation();

	uint8 latBands = 20;
	uint8 longBands = 20;

	StaticMaths::AddSphereToCellMesh(latBands, longBands, radiusTemp, centerOffsetTemp, &vertices, &normals, &indices);

	//After the base node continue with its children
	//Offset when adding to the index buffer is always the length of the vertex buffer when starting a new sphere
	//This iteration over children has to be done 4x
	TArray<EPosition> pos = baseNode->GetChildrenPositions();
	for(uint8 i = 0; i < pos.Num(); i++)
	{
		UCellEditor_NodeComponent* curNode = baseNode->GetChild(pos[i]);
		centerOffsetTemp = curNode->GetRelativeTransform().GetLocation();
		radiusTemp = curNode->GetRadius();
		//Get current child node of the base and add its sphere
		StaticMaths::AddSphereToCellMesh(latBands, longBands, radiusTemp, centerOffsetTemp, &vertices, &normals, &indices);

		//Move on along the arm of this node one step
		TArray<EPosition> pos_2 = curNode->GetChildrenPositions();
		for(uint8 i_2 = 0; i_2 < pos_2.Num(); i_2 ++)
		{
			UCellEditor_NodeComponent* curNode_2 = curNode->GetChild(pos[i]);
			centerOffsetTemp = curNode_2->GetRelativeTransform().GetLocation();
			radiusTemp = curNode_2->GetRadius();
			StaticMaths::AddSphereToCellMesh(latBands, longBands, radiusTemp, centerOffsetTemp, &vertices, &normals, &indices);

			TArray<EPosition> pos_3 = curNode_2->GetChildrenPositions();
			for(uint8 i_3 = 0; i_3 < pos_3.Num(); i_3 ++)
			{
				UCellEditor_NodeComponent* curNode_3 = curNode_2->GetChild(pos[i]);
				centerOffsetTemp = curNode_3->GetRelativeTransform().GetLocation();
				radiusTemp = curNode_3->GetRadius();
				StaticMaths::AddSphereToCellMesh(latBands, longBands, radiusTemp, centerOffsetTemp, &vertices, &normals, &indices);

				TArray<EPosition> pos_4 = curNode_3->GetChildrenPositions();
				for(uint8 i_4 = 0; i_4 < pos_4.Num(); i_4 ++)
				{
					UCellEditor_NodeComponent* curNode_4 = curNode_3->GetChild(pos[i]);
					centerOffsetTemp = curNode_4->GetRelativeTransform().GetLocation();
					radiusTemp = curNode_4->GetRadius();
					StaticMaths::AddSphereToCellMesh(latBands, longBands, radiusTemp, centerOffsetTemp, &vertices, &normals, &indices);
				}
			}
		}
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

	bodyMesh->CreateMeshSection_LinearColor(0, vertices, indices, normals, {}, {}, {}, true);
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

int AEditorBase_Cell::GetIdCounter()
{
	idCounter++;
	return idCounter;
}