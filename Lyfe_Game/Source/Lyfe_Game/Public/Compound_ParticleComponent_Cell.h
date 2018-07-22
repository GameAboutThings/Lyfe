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

	/** The value of this one particle */
	uint8 value;
protected:
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	void Consumption(AActor* consumer);

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	void BeginOverlap(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//void BeginOverlap(AActor* otherActor);

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	void EndOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex);
public:
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|FX")
	class UParticleSystemComponent* GetParticleSystem();

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	class UStaticMeshComponent* GetMesh();
};
