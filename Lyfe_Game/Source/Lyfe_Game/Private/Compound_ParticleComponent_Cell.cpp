// Fill out your copyright notice in the Description page of Project Settings.

#include "Compound_ParticleComponent_Cell.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "CompoundCloud_Cell.h"
#include "Logging.h"
#include <string>


// Sets default values for this component's properties
UCompound_ParticleComponent_Cell::UCompound_ParticleComponent_Cell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//The mesh not as a component but directly as mesh in this component
	auto psAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("ParticleSystem'/Game/ParticleSystems/PS_CompoundCloud_SingleCelled.PS_CompoundCloud_SingleCelled'"));
	if (psAsset.Object != nullptr)
	{
		particleSystemType = psAsset.Object;
	}
	else
	{
		Logging::Log("Could not find Asset at path in Compound_ParticleComponent_Cell");
	}

	ACompoundCloud_Cell* parentCloud = Cast<ACompoundCloud_Cell>(this->GetOwner());
	if (parentCloud != nullptr)
	{
		TArray<FVector> vertices = parentCloud->GetVertices();

		for (int i = 0; i < vertices.Num(); i++)
		{			
			std::string name = "ParticleSystem_";
			name.append({ static_cast<char>(i) });
			
			particleSystems.Add(CreateDefaultSubobject<UParticleSystemComponent>(name.c_str()));
			particleSystems[i]->AttachTo(parentCloud->GetRootComponent());
			particleSystems[i]->SetRelativeLocation(vertices[i]);
			particleSystems[i]->Template = particleSystemType;
			//particleSystems[i]->SetActive(true);
			particleSystems[i]->ActivateSystem(true);
			//particleSystems[i]->bIsActive = true;
			particleSystems[i]->bVisible = true;
		}
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

void UCompound_ParticleComponent_Cell::UpdateSpawnPositions(TArray<FVector> vertices, TArray<int32> indices)
{

}

TArray<class UParticleSystemComponent*> UCompound_ParticleComponent_Cell::GetParticleSystems()
{
	return particleSystems;
}

