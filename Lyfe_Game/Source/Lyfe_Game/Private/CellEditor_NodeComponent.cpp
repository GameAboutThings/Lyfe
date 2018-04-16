// Fill out your copyright notice in the Description page of Project Settings.

#include "CellEditor_NodeComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Logging.h"


// Sets default values for this component's properties
UCellEditor_NodeComponent::UCellEditor_NodeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//Create the visual representation for this node
	sphereRepresentation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	sphereRepresentation->SetupAttachment(this);
}


// Called when the game starts
void UCellEditor_NodeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCellEditor_NodeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
void UCellEditor_NodeComponent::SetType(ENodeType newType)
{
	this->type = newType;
}

UStaticMeshComponent * UCellEditor_NodeComponent::GetMesh()
{
	return sphereRepresentation;
}

void UCellEditor_NodeComponent::AttachChildNode(EPosition position)
{
	if(position == EPosition::EAbove)
	{
		baseChild1 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Above"));
		baseChild1->SetupAttachment(this);
		baseChild1->SetRelativeLocation(FVector(EDITOR_NODE_DISTANCE, 0.f, 0.f));
	}
	else if(position == EPosition::ERight)
	{
		baseChild2 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Right"));
		baseChild2->SetupAttachment(this);
		baseChild2->SetRelativeLocation(FVector(0.f, EDITOR_NODE_DISTANCE, 0.f));
	}
	else if(position == EPosition::EBelow)
	{
		baseChild3 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Below"));
		baseChild3->SetupAttachment(this);
		baseChild3->SetRelativeLocation(FVector(-EDITOR_NODE_DISTANCE, 0.f, 0.f));
	}
	else if(position == EPosition::ELeft)
	{
		baseChild4 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Left"));
		baseChild4->SetupAttachment(this);
		baseChild2->SetRelativeLocation(FVector(0.f, -EDITOR_NODE_DISTANCE, 0.f));
	}
}

void UCellEditor_NodeComponent::AttachChildNode()
{
	child = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode"));
	child->SetupAttachment(this);

	UCellEditor_NodeComponent* parentNode = Cast<UCellEditor_NodeComponent>(this->GetOwner());
	if(parentNode != nullptr)
	{
		FVector pos = this->GetRelativeLocation();
		FVector parPos = parentNode->GetRelativeLocation();
		FVector childPos = pos - parPos;
		child->SetRelativeLocation(childPos);
	}
	else
	{
		Logging::Log("No parent node could be found", true);
	}
}

UCellEditor_NodeComponent* UCellEditor_NodeComponent::GetChild(EPosition position)
{
	if(position == EPosition::EAbove)
	{
		return baseChild1;
	}
	else if(position == EPosition::ERight)
	{
		return baseChild2;
	}
	else if(position == EPosition::EBelow)
	{
		return baseChild3;
	}
	else if(position == EPosition::ELeft)
	{
		return baseChild4;
	}
}

UCellEditor_NodeComponent* UCellEditor_NodeComponent::GetChild()
{
	return child;
}
