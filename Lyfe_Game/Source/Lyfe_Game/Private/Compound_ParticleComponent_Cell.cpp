// Fill out your copyright notice in the Description page of Project Settings.

#include "Compound_ParticleComponent_Cell.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "CompoundCloud_Cell.h"
#include "Logging.h"
#include <string>
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CompoundStorageComponent_Cell.h"


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
	

	//get the mesh and set it
	auto meshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/ball.ball'"));
	if (meshAsset.Object != nullptr)
	{
		mesh->SetStaticMesh(meshAsset.Object);
		//mesh->SetVisibility(false);
	}
	else
	{
		Logging::Log("Could not find Asset 'ball' at path in Compound_ParticleComponent_Cell");
	}

	//get the needed particle system and set it in the component
	//For some fucking reason this line might give some trouble
	try
	{
		//static ConstructorHelpers::FObjectFinder<UParticleSystem> psAsset(TEXT("ParticleSystem'/Game/ParticleSystems/PS_CompoundCloud_SingleCelled.PS_CompoundCloud_SingleCelled'"));
		auto psAsset = ConstructorHelpers::FObjectFinderOptional<UParticleSystem>(TEXT("'/Game/ParticleSystems/PS_CompoundCloud.PS_CompoundCloud'"));
		if (psAsset.Succeeded())
		{
			particleSystemType = psAsset.Get();
		}
		else
		{
			Logging::Log("Could not find Asset 'PS_CompoundCloud_SingleCelled' at path in Compound_ParticleComponent_Cell");
		}
		//particleSystem->Template = particleSystemType;
		particleSystem->SetTemplate(particleSystemType);
	}
	catch (int e)
	{
		Logging::Log("Could not find Asset 'PS_CompoundCloud_SingleCelled' at path in Compound_ParticleComponent_Cell\nCause: FObjectFinder Access Violation");
		Logging::Log(e);
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
void UCompound_ParticleComponent_Cell::Consumption()
{
	ACompoundCloud_Cell* parent = Cast<ACompoundCloud_Cell>(GetOwner());
	if(parent != nullptr)
	{
		parent->AddValue(-1);

		ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (controller != nullptr)
		{
			controller->GetCompoundStorage()->AddCompound(value, parent->GetType());
		}
		else
		{
			Logging::Log("ERROR in Consumption: controller could not be referenced ", true);
		}

		this->DestroyComponent();
	}
	else
	{
		Logging::Log("ERROR in Consumption: parent could not be referenced ", true);
	}	
}

void UCompound_ParticleComponent_Cell::BeginOverlap(AActor* otherActor)
{
	if ((otherActor != nullptr) /*&& (otherActor != this)*/)
	{
		//If the player is on the compound cloud
		ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(otherActor);
		if (controller != nullptr)
		{
			Consumption();
		}

		//If a cell is on the compound cloud
	}
}

void UCompound_ParticleComponent_Cell::EndOverlap(AActor* otherActor)
{
	if ((otherActor != nullptr) /*&& (otherActor != this)*/)
	{
		//If the player is on the compound cloud
		ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(otherActor);
		if (controller != nullptr)
		{

		}


		//If a cell is on the compound cloud
	}
}

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