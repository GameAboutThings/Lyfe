// Fill out your copyright notice in the Description page of Project Settings.

#include "CellEditor_NodeComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


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

void UCellEditor_NodeComponent::SetType(ENodeType newType)
{
	this->type = newType;
}

UStaticMeshComponent * UCellEditor_NodeComponent::GetMesh()
{
	return sphereRepresentation;
}

