// Fill out your copyright notice in the Description page of Project Settings.

#include "CellEditor_ArrowComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Logging.h"

// Sets default values for this component's properties
UCellEditor_ArrowComponent::UCellEditor_ArrowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Create the visual representation for this arrow
	//arrowRepresentation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowRepresentation"));
	//arrowRepresentation->SetupAttachment(this);

	//The mesh not as a component but directly as mesh in this component
	auto meshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/Arrow.Arrow'"));
	if (meshAsset.Object != nullptr)
	{
		arrowRepresentation = meshAsset.Object;
		SetStaticMesh(arrowRepresentation);
	}
	else
	{
		Logging::Log("Could not find Asset at path in CellEditor_ArrowComponent()");
	}
}


// Called when the game starts
void UCellEditor_ArrowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCellEditor_ArrowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
UStaticMeshComponent * UCellEditor_ArrowComponent::GetMeshComponent()
{
	return nullptr;// arrowRepresentation;
}

