// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Compound_ParticleComponent_Cell.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYFE_GAME_API UCompound_ParticleComponent_Cell : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCompound_ParticleComponent_Cell();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
/*---------------------------------------------------------------------------------------*/


  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////// CLASSES | STRUCTS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////
private:
protected:
public:

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// VARIABLES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
private:
	UPROPERTY(VisibleAnywhere, Category = "CELL|CompoundCloud|FX")
	TArray<class UParticleSystemComponent* > particleSystems;

	UPROPERTY(EditAnywhere, Category = "CELL|CompoundCloud|FX")
	class UParticleSystem* particleSystemType;
protected:
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:

	/** Give the spawn positions for the particle systems
	* @param vertices The vertices of the procedural mesh
	* @param indices The indices of the procedural mesh (not used currently)
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|FX")
	void UpdateSpawnPositions(TArray<FVector> vertices, TArray<int32> indices);

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|FX")
	TArray<class UParticleSystemComponent*> GetParticleSystems();
};
