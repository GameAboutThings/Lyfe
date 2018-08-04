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
#include "Runtime/Engine/Classes/Engine/World.h"
#include "StaticMaths.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"


// Sets default values for this component's properties
UCompound_ParticleComponent_Cell::UCompound_ParticleComponent_Cell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Set value for this one blob
	value = StaticMaths::RR(50, 100);

	//instantiate mesh component and particle system component
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	particleSystem->SetupAttachment(this);
	mesh->SetupAttachment(this);
	
	//Collision binding
	mesh->bGenerateOverlapEvents = true;
	mesh->OnComponentBeginOverlap.AddDynamic(this, &UCompound_ParticleComponent_Cell::BeginOverlap);
	mesh->OnComponentEndOverlap.AddDynamic(this, &UCompound_ParticleComponent_Cell::EndOverlap);


	//get the mesh and set it
	auto meshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/ball.ball'"));
	if (meshAsset.Object != nullptr)
	{
		mesh->SetStaticMesh(meshAsset.Object);
		mesh->SetVisibility(false);
		mesh->RelativeScale3D = FVector(5.f);
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
		auto psAsset = ConstructorHelpers::FObjectFinderOptional<UParticleSystem>(TEXT("ParticleSystem'/Game/ParticleSystems/PS_CompoundCloud_SingleCelled.PS_CompoundCloud_SingleCelled'"));
		if (psAsset.Succeeded())
		{
			particleSystemType = psAsset.Get();
			particleSystem->SetTemplate(particleSystemType);
		}
		else
		{
			Logging::Log("Could not find Asset 'PS_CompoundCloud_SingleCelled' at path in Compound_ParticleComponent_Cell");
		}
		//particleSystem->Template = particleSystemType;
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
	SetColorToType();
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


void UCompound_ParticleComponent_Cell::SetColorToType()
{
	//generate cloud color:
	FColor color = FColor(1.f, 1.f, 1.f, 1.f);

	ACompoundCloud_Cell* cloud = Cast<ACompoundCloud_Cell>(this->GetOwner());
	if (cloud == nullptr)
	{
		Logging::Log("Parent Cloud for particleComponent returned nullptr.");
		return;
	}
	TEnumAsByte<ECompound> type = cloud->GetType();

	switch (type)
	{
	case ECompound::ECO2:
		color = FColor(0.6, 1, 0.8, 1);
		break;
	case ECompound::EO2:
		color = FColor(1, 0.6, 0.4, 1);
		break;
	case ECompound::EAminoAcid:
		color = FColor(0.4, 1, 0.6, 1);
		break;
	case ECompound::EGlucose:
		color = FColor(1, 1, 1, 1);
		break;
	case ECompound::ELipid:
		color = FColor(1, 1, 0.6, 1);
		break;
	default:
		color = FColor(1, 1, 1, 1);
		break;
	}

	//change the color of the particle system
	if (particleSystem != nullptr)
	{
		UMaterialInterface* material = particleSystem->GetMaterial(0);
		if (material != nullptr)
		{
			UMaterialInstanceDynamic* dynMaterial = UMaterialInstanceDynamic::Create(material, this);
			if (dynMaterial != nullptr)
			{
				Logging::Log(color);
				dynMaterial->SetVectorParameterValue(FName("Color"), color);
				particleSystem->SetMaterial(0, dynMaterial);
				//particleSystem->SetMaterialByName(FName("Material"), dynMaterial);
				//particleSystem->SetVectorParameter(FName("Color"), FVector(color));
			}
			else
			{
				Logging::Log("Dynamic Material in CompoundCloud_Cell constructor is nullptr.");
			}
		}
		else
		{
			Logging::Log("Material in CompoundCloud_Cell constructor is nullptr.");
		}
	}
	else
	{
		Logging::Log("ParticleSystem in CompoundCloud_Cell constructor is nullptr.");
	}
}

//////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void UCompound_ParticleComponent_Cell::Consumption(AActor* consumer)
{
	if (consumer == nullptr)
	{
		Logging::Log("ERROR on CompoundCloud consumption: consumer is nullptr");
		return;
	}

	ACompoundCloud_Cell* parent = Cast<ACompoundCloud_Cell>(GetOwner());
	if (parent == nullptr)
	{
		Logging::Log("ERROR on CompoundCloud consumption: parent of particleComponent could not be referenced");
		return;
	}
		

	parent->AddValue(-1);

	//If the player is on the compound cloud
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(consumer);

	if (controller != nullptr)//consumer == player
	{
		controller->GetCompoundStorage()->AddCompound(value, parent->GetType());
	}
	else //consumer == other random object
	{
		FString c = consumer->GetClass()->GetName();
		Logging::Log(c, "Consumer of class ");
	}
	mesh->UnregisterComponent();
	particleSystem->UnregisterComponent();
	this->UnregisterComponent();
}

void UCompound_ParticleComponent_Cell::BeginOverlap(class UPrimitiveComponent* newComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	ACompoundCloud_Cell* parent = Cast<ACompoundCloud_Cell>(this->GetOwner());
	if (parent == nullptr)
		return;


	if ((otherActor != nullptr) && (otherActor != parent))
	{
		Consumption(otherActor);
	}
}

void UCompound_ParticleComponent_Cell::EndOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex)
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

void UCompound_ParticleComponent_Cell::DestroyComponent()
{
	mesh->UnregisterComponent();
	particleSystem->UnregisterComponent();
	this->UnregisterComponent();
}
