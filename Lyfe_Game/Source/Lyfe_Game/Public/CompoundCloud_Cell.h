// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Compound_ParticleComponent_Cell.h"
#include "Meta_CellStage.h"
#include "CompoundCloud_Cell.generated.h"


UCLASS()
class LYFE_GAME_API ACompoundCloud_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACompoundCloud_Cell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	/** The count of Compound_ParticleComponent_Cells */
	UPROPERTY()
	uint32 value;

	//UPROPERTY()
	//bool bBeingConsumed;

	UPROPERTY()
	FTimerHandle despawnTimer;

	/** The type of this compound cloud */
	UPROPERTY()
	TEnumAsByte<ECompound> type;

protected:
	/** The editable mesh for the compound cloud */
	//UPROPERTY(BlueprintReadWrite, Category = "CELL|CompoundCloud|Mesh")
	//UProceduralMeshComponent * mesh;

	/** This array contains all the particles that can be consumed by the player*/
	UPROPERTY(VisibleAnywhere, Category = "CELL|CompoundCloud|FX")
	TArray<UCompound_ParticleComponent_Cell *> particles;

public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	/** Mostly in here as an example */
	void CreateCube();

	UFUNCTION()
	void CloudFinishConsumption();

	/** Called every 5 seconds 
	 * Despawns the compound cloud if the player is too far away
	*/
	UFUNCTION()
	void DespawnTick();

protected:
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	void BeginOverlap(AActor* otherActor);

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Collision")
	void EndOverlap(AActor* otherActor);


public:
	/** Returns the type of the Compound Cloud as the Compound Enum*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Compound")
	ECompound GetType();

	/** Returns the vertices for the procedural mesh*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Mesh")
	TArray<FVector> GetVertices();

	/** Returns the indices for the procedural mesh*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Mesh")
	TArray<int32> GetIndices();

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Mesh")
	UProceduralMeshComponent* GetMesh();

	/** Allows to manipulate the value of this compound cloud
	 * @param amount positive or negative
	*/
	UFUNCTION()
	void AddValue(int amount);

	/** 
	* @return Array with all particle systems for the cloud representation
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Compound")
	TArray<UCompound_ParticleComponent_Cell*> GetParticleComponents();
};
