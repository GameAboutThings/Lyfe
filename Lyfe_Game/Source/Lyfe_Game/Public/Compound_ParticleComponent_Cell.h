// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Compound_ParticleComponent_Cell.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYFE_GAME_API UCompound_ParticleComponent_Cell : public USceneComponent
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
	class UParticleSystemComponent* particleSystem;

	UPROPERTY(EditAnywhere, Category = "CELL|CompoundCloud|FX")
	class UParticleSystem* particleSystemType;

	UPROPERTY(EditAnywhere, Category = "CELL|CompoundCloud|Collision")
	class UStaticMeshComponent* mesh;
protected:
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|FX")
	class UParticleSystemComponent* GetParticleSystem();

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	class UStaticMeshComponent* GetMesh();
};
