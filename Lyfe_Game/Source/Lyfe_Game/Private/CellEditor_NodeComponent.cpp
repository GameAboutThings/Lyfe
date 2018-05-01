// Fill out your copyright notice in the Description page of Project Settings.

#include "CellEditor_NodeComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Logging.h"
#include "Runtime/Engine/Public/PrimitiveSceneProxy.h"
#include "StaticMaths.h"
#include "CellEditor_ArrowComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"


// Sets default values for this component's properties
UCellEditor_NodeComponent::UCellEditor_NodeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	auto meshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/Ball.Ball'"));
	if (meshAsset.Object != nullptr)
	{
		sphereRepresentation = meshAsset.Object;
		SetStaticMesh(sphereRepresentation);
	}
	else
	{
		Logging::Log("Could not find Asset at path in CellEditor_NodeComponent()");
	}

	auto materialAsset = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/M_Editor_Node.M_Editor_Node'"));
	if (materialAsset.Object != nullptr)
	{
		//UStaticMesh* mesh = this->GetStaticMesh();
		UMaterialInterface * mInterface = Cast<UMaterialInterface>(materialAsset.Object);
		if (mInterface != nullptr)
		{
			SetMaterial(0, materialAsset.Object);
		}
		else
		{
			Logging::Log("Couldn't cast material to interface");
		}
	}
	else
	{
		Logging::Log("Could not find Asset at path '/Game/Materials/M_Editor_Node.M_Editor_Node' in CellEditor_NodeComponent.PostConstructor");
	}

	//Create the 4 arrows that are used for creating and deleting nodes
	arrowUp = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("UP"));
	arrowUp->SetupAttachment(this);
	arrowUp->AddRelativeLocation(FVector(EDITOR_ARROW_DISTANCEFROMBASE, 0.f, 0.f));
	arrowUp->SetRelativeRotation(FRotator(-90, 0, 0));

	arrowDown = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("DOWN"));
	arrowDown->SetupAttachment(this);
	arrowDown->AddRelativeLocation(FVector(-EDITOR_ARROW_DISTANCEFROMBASE, 0.f, 0.f));
	arrowDown->SetRelativeRotation(FRotator(90, 0, 0));

	arrowLeft = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("LEFT"));
	arrowLeft->SetupAttachment(this);
	arrowLeft->AddRelativeLocation(FVector(0.f, -EDITOR_ARROW_DISTANCEFROMBASE, 0.f));
	arrowLeft->SetRelativeRotation(FRotator(0, 0, -90));

	arrowRight = CreateDefaultSubobject<UCellEditor_ArrowComponent>(TEXT("RIGHT"));
	arrowRight->SetupAttachment(this);
	arrowRight->AddRelativeLocation(FVector(0.f, EDITOR_ARROW_DISTANCEFROMBASE, 0.f));
	arrowRight->SetRelativeRotation(FRotator(0, 0, 90));
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
void UCellEditor_NodeComponent::PostConstructor(ENodeType _eNewType, EPosition _eNewPositionToParent)
{
	this->_eType = _eNewType;
	this->_ePositionToParent = _eNewPositionToParent;
}

ENodeType UCellEditor_NodeComponent::GetType()
{
	return _eType;
}

UStaticMesh * UCellEditor_NodeComponent::GetMesh()
{
	return sphereRepresentation;
}

void UCellEditor_NodeComponent::CreateAndAttachChildNode(EPosition position)
{
	//Get vector to parent node if this isn't the base
	FVector childPos;
	if (_eType != ENodeType::EBase)
	{
		UCellEditor_NodeComponent* parentNode = Cast<UCellEditor_NodeComponent>(this->GetOwner());
		if (parentNode != nullptr)
		{
			FVector pos = this->GetRelativeTransform().GetLocation();
			FVector parPos = parentNode->GetRelativeTransform().GetLocation();
			FVector dir = StaticMaths::Normalized(pos - parPos);
			childPos = (pos + dir) * EDITOR_NODE_DISTANCE;
		}
		else
		{
			Logging::Log("No parent node could be found", true);
		}
	}

	//These ifs make sure that you can't create a child node on the socket where a parent node is attached
	if(position == EPosition::EAbove && _ePositionToParent != EPosition::EBelow)
	{
		child1 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Above"));
		child1->SetupAttachment(this);
		//child1->SetRelativeLocation(FVector(EDITOR_NODE_DISTANCE, 0.f, 0.f));
		child1->SetRelativeLocation(childPos);
		arrowUp->DestroyComponent();
		arrowUp = nullptr;
	}
	else if(position == EPosition::ERight && _ePositionToParent != EPosition::ELeft)
	{
		child2 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Right"));
		child2->SetupAttachment(this);
		//child2->SetRelativeLocation(FVector(0.f, EDITOR_NODE_DISTANCE, 0.f));
		child2->SetRelativeLocation(childPos);
		arrowRight->DestroyComponent();
		arrowRight = nullptr;
	}
	else if(position == EPosition::EBelow && _ePositionToParent != EPosition::EAbove)
	{
		child3 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Below"));
		child3->SetupAttachment(this);
		//child3->SetRelativeLocation(FVector(-EDITOR_NODE_DISTANCE, 0.f, 0.f));
		child3->SetRelativeLocation(childPos);
		arrowDown->DestroyComponent();
		arrowDown = nullptr;
	}
	else if(position == EPosition::ELeft && _ePositionToParent != EPosition::ERight)
	{
		child4 = CreateDefaultSubobject<UCellEditor_NodeComponent>(TEXT("ChildNode_Left"));
		child4->SetupAttachment(this);
		//child4->SetRelativeLocation(FVector(0.f, -EDITOR_NODE_DISTANCE, 0.f));
		child4->SetRelativeLocation(childPos);
		arrowLeft->DestroyComponent();
		arrowLeft = nullptr;
	}
	else
	{
		Logging::Log("Position of Node in conflict with position of childnode you want to create");
	}
}

UCellEditor_NodeComponent* UCellEditor_NodeComponent::GetChild(EPosition position)
{
	if(position == EPosition::EAbove)
	{
		return child1;
	}
	else if(position == EPosition::ERight)
	{
		return child2;
	}
	else if(position == EPosition::EBelow)
	{
		return child3;
	}
	else if(position == EPosition::ELeft)
	{
		return child4;
	}

	return nullptr;
}

TArray<EPosition> UCellEditor_NodeComponent::GetChildrenPositions()
{
	TArray<EPosition> positions;

	if (child1 != nullptr)
	{
		positions.Add(EPosition::EAbove);
	}
	if (child2 != nullptr)
	{
		positions.Add(EPosition::ERight);
	}
	if (child3 != nullptr)
	{
		positions.Add(EPosition::EBelow);
	}
	if (child4 != nullptr)
	{
		positions.Add(EPosition::ELeft);
	}

	return positions;
}

EPosition UCellEditor_NodeComponent::GetPositionToParent()
{
	return _ePositionToParent;
}

void UCellEditor_NodeComponent::SwitchNodePosition(EPosition _eTargetPosition)
{
	if (_eType != ENodeType::EBase)
	{
		UCellEditor_NodeComponent* parentNode = Cast<UCellEditor_NodeComponent>(this->GetOwner());
		if (parentNode != nullptr)
		{
			if (parentNode->GetChild(_eTargetPosition) != nullptr)
			{
				Logging::Log("Could not switch node position; Target position already occupied");
			}
			else
			{
				//Set node on new position
				parentNode->SetChildNode(_eTargetPosition, this);
				parentNode->SetChildNode(_ePositionToParent, nullptr);
				_ePositionToParent = _eTargetPosition;
			}
		}
		else
		{
			Logging::Log("No parent node could be found", true);
		}
	}
	else
	{
		Logging::Log("Can't switch position of base node");
	}
}

void UCellEditor_NodeComponent::SetType(ENodeType _eNewType)
{
	this->_eType = _eNewType;
}

void UCellEditor_NodeComponent::SetChildNode(EPosition _ePosition, UCellEditor_NodeComponent * node)
{
	if ((_ePosition == EPosition::EAbove && child1 == nullptr) || node == nullptr)
	{
		child1 = node;
	}
	else if ((_ePosition == EPosition::ERight && child2 == nullptr) || node == nullptr)
	{
		child2 = node;
	}
	else if ((_ePosition == EPosition::EBelow && child3 == nullptr) || node == nullptr)
	{
		child3 = node;
	}
	else if ((_ePosition == EPosition::ELeft && child4 == nullptr) || node == nullptr)
	{
		child4 = node;
	}
}
