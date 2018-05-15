// Fill out your copyright notice in the Description page of Project Settings.

#include "Compound_ParticleComponent_Cell.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "CompoundCloud_Cell.h"
#include "Logging.h"
#include <string>
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UCompound_ParticleComponent_Cell::UCompound_ParticleComponent_Cell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//instantiate mesh component and particle system component
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	particleSystem->SetupAttachment(this);
	mesh->SetupAttachment(this);

	//get the needed particle system and set it in the component
	auto psAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/ParticleSystems/PS_CompoundCloud_SingleCelled.PS_CompoundCloud_SingleCelled'"));
	if (psAsset.Object != nullptr)
	{
		particleSystemType = psAsset.Object;
	}
	else
	{
		Logging::Log("Could not find Asset 'PS_CompoundCloud_SingleCelled' at path in Compound_ParticleComponent_Cell");
	}
	particleSystem->Template = particleSystemType;

	//get the mesh and set it
	auto meshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/ball.ball'"));
	if (meshAsset.Object != nullptr)
	{
		mesh->SetStaticMesh(meshAsset.Object);
	}
	else
	{
		Logging::Log("Could not find Asset 'ball' at path in Compound_ParticleComponent_Cell");
	}
	
}


// Called when the game starts
void UCompound_ParticleComponent_Cell::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCompound_ParticleComponent_Cell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
/* ------------------------------------------------------------------------------------------------- */

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class UParticleSystemComponent* UCompound_ParticleComponent_Cell::GetParticleSystem()
{
	return particleSystem;
}

UStaticMeshComponent * UCompound_ParticleComponent_Cell::GetMesh()
{
	return mesh;
}

