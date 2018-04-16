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
	baseNode->SetType(ENodeType::EBase);

	//Create the 4 arrows that are used for creating and deleting nodes
	arrowUp = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("UP"));
	arrowUp->SetupAttachment(RootComponent);
	arrowUp->AddRelativeLocation(FVector(EDITOR_ARROW_DISTANCEFROMBASE, 0.f, 0.f));
	arrowUp->SetRelativeRotation(FRotator(90, 0, 0));

	arrowDown = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("DOWN"));
	arrowDown->SetupAttachment(RootComponent);
	arrowDown->AddRelativeLocation(FVector(-EDITOR_ARROW_DISTANCEFROMBASE, 0.f, 0.f));
	arrowUp->SetRelativeRotation(FRotator(0, 90, 0));

	arrowLeft = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("LEFT"));
	arrowLeft->SetupAttachment(RootComponent);
	arrowLeft->AddRelativeLocation(FVector(0.f, -EDITOR_ARROW_DISTANCEFROMBASE, 0.f));
	arrowUp->SetRelativeRotation(FRotator(-90, 0, 0));

	arrowRight = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("RIGHT"));
	arrowRight->SetupAttachment(RootComponent);
	arrowRight->AddRelativeLocation(FVector(0.f, EDITOR_ARROW_DISTANCEFROMBASE, 0.f));
	arrowUp->SetRelativeRotation(FRotator(0, -90, 0));

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