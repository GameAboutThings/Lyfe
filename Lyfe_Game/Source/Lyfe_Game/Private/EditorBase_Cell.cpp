// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorBase_Cell.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "CellEditor_NodeComponent.h"
#include "CellEditor_ArrowComponent.h"
#include "StaticMaths.h"
#include "ProceduralMeshComponent.h"
#include "Meta_CellEditor.h"
#include "Logging.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

// Sets default values
AEditorBase_Cell::AEditorBase_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	idCounter = 0;

	//inputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputHandler"));
	//inputComponent->BindAxis(FName("Scroll"));

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
}

// Called when the game starts or when spawned
void AEditorBase_Cell::BeginPlay()
{
	Super::BeginPlay();
	idCounter = 0;

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (playerController != nullptr)
	{
		EnableInput(playerController);
		playerController->bEnableMouseOverEvents = true;
	}

	baseNode->CreateAndAttachChildNode(EPosition::ELeft);
	//baseNode->CreateAndAttachChildNode(EPosition::EBelow);
	//baseNode->GetChild(baseNode->GetChildrenPositions()[0])->CreateAndAttachChildNode(EPosition::ELeft);
	//baseNode->GetChild(baseNode->GetChildrenPositions()[1])->CreateAndAttachChildNode(EPosition::EBelow);
	//baseNode->GetChild(baseNode->GetChildrenPositions()[0])->GetChild(baseNode->GetChildrenPositions()[0])->CreateAndAttachChildNode(EPosition::ELeft);
	//baseNode->GetChild(baseNode->GetChildrenPositions()[1])->GetChild(baseNode->GetChildrenPositions()[0])->CreateAndAttachChildNode(EPosition::ELeft);
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

void AEditorBase_Cell::AddChildNodes(TArray<UCellEditor_NodeComponent*>* nodes, UCellEditor_NodeComponent* parentNode)
{
	TArray<EPosition> childrenPositions = parentNode->GetChildrenPositions();

	for (int i = 0; i < childrenPositions.Num(); i++)
	{
		nodes->Add(parentNode->GetChild(childrenPositions[i]));
		AddChildNodes(nodes, parentNode->GetChild(childrenPositions[i]));
	}
}

FVector AEditorBase_Cell::GridPosToLocalPos(FVector gridPos)
{
	FVector localPos = gridPos;
	localPos.X -= EDITOR_GRID_DIMENSION_X / 2;
	localPos.Y -= EDITOR_GRID_DIMENSION_Y / 2;
	localPos.Z -= EDITOR_GRID_DIMENSION_Z / 2;

	localPos *= EDITOR_GRID_SCALE;

	return localPos + GetActorLocation();
}

FVector AEditorBase_Cell::NodePosToLocalPos(UCellEditor_NodeComponent * node)
{
	return node->GetComponentToWorld().GetLocation() - baseNode->GetComponentToWorld().GetLocation();
}

float AEditorBase_Cell::CalculateCharge(FVector nodePos, FVector voxelPos, float cubePortion, FVector distortion, float mag)
{
	return 1 / (cubePortion * CalculateCubeCharge(nodePos, voxelPos, distortion, mag) + (1 - cubePortion) * CalculateSphereCharge(nodePos, voxelPos, distortion, mag));
}

float AEditorBase_Cell::CalculateCubeCharge(FVector nodePos, FVector voxelPos, FVector distortion, float mag)
{
	return 1.0f;
}

float AEditorBase_Cell::CalculateSphereCharge(FVector nodePos, FVector voxelPos, FVector distortion, float mag)
{
	float dx = FMath::Pow(voxelPos.X - nodePos.X, 2);
	float dy = FMath::Pow(voxelPos.Y - nodePos.Y, 2);
	float dz = FMath::Pow(voxelPos.Z - nodePos.Z, 2);

	float r_squared = (dx * distortion.X + dy * distortion.Y + dz * distortion.Z) / FMath::Pow(mag, 2);

	//if(r_squared < 0.5f) //or Mathf.Sqrt(r_squared) < 0.707f
	//{
	return 0.25f - r_squared + FMath::Pow(r_squared, 2);
	//}
	//return 0;
}



  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void AEditorBase_Cell::GenerateBodyMesh()
{
	//TODO rebuild this function so it actually generates a mesh and not just a lot of cubes

	//3 dimensional grid for chargeValues that determine if there is a voxel or not
	float*** chargeValues = new float**[EDITOR_GRID_DIMENSION_Z];
	for (int i = 0; i < EDITOR_GRID_DIMENSION_Z; i++)
	{
		chargeValues[i] = new float *[EDITOR_GRID_DIMENSION_Y]();
		for (int j = 0; j < EDITOR_GRID_DIMENSION_Y; j++)
			chargeValues[i][j] = new float[EDITOR_GRID_DIMENSION_X]();
	}

	TArray<UCellEditor_NodeComponent*> nodes;// = new TArray<UCellEditor_NodeComponent*>();

	////Go through all level of nodes
	nodes.Add(baseNode);
	AddChildNodes(&nodes, baseNode);
	FVector voxelPos;
	FVector nodePos;
	FVector voxel;


	for (uint8 n = 0; n < nodes.Num(); n++)
	{
		for (voxel.Z = 0; voxel.Z < EDITOR_GRID_DIMENSION_Z; voxel.Z ++)
		{
			for (voxel.Y = 0; voxel.Y < EDITOR_GRID_DIMENSION_Y; voxel.Y ++)
			{
				for (voxel.X = 0; voxel.X < EDITOR_GRID_DIMENSION_X; voxel.X ++)
				{
					if (chargeValues[FMath::FloorToInt(voxel.Z)][FMath::FloorToInt(voxel.Y)][FMath::FloorToInt(voxel.X)] < EDITOR_METABALLS_THRESHOLD)
					{
						voxelPos = GridPosToLocalPos(voxel);
						nodePos = NodePosToLocalPos(nodes[n]);
						float chargeTmp = CalculateCharge(nodePos, voxelPos, nodes[n]->GetCubePortion(), nodes[n]->GetDistortion(), nodes[n]->GetRadius() * EDITOR_GRID_SCALE);

						chargeValues[FMath::FloorToInt(voxel.Z)][FMath::FloorToInt(voxel.Y)][FMath::FloorToInt(voxel.X)] += chargeTmp;
						//chargeValues[FMath::FloorToInt(voxel.Z)][FMath::FloorToInt(voxel.Y)][FMath::FloorToInt(voxel.X)] /= 1.5f;
						
						if (chargeValues[FMath::FloorToInt(voxel.Z)][FMath::FloorToInt(voxel.Y)][FMath::FloorToInt(voxel.X)] >= EDITOR_METABALLS_THRESHOLD)
						{
							DrawDebugBox(GetWorld(), voxelPos, FVector(EDITOR_GRID_SCALE), FColor(225,225,225), true, -1);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < EDITOR_GRID_DIMENSION_Z; i++)
	{
		for (int j = 0; j < EDITOR_GRID_DIMENSION_Y; j++)
			delete[] chargeValues[i][j];
		delete[] chargeValues[i];
	}
	delete[] chargeValues;
}

int AEditorBase_Cell::GetIdCounter()
{
	idCounter++;
	return idCounter;
}