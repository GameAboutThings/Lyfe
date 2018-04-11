// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Meta_CellStage.h"

#include "CompoundCloud_Cell.generated.h"

USTRUCT(BlueprintType)
struct FMeshBounds
{
	GENERATED_BODY()

	float zero;
	float one;
	float two;
	float three;
	float four;
};

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
	UPROPERTY()
	uint32 value;

	UPROPERTY()
	bool bBeingConsumed;

	UPROPERTY()
	FTimerHandle despawnTimer;

	/** The type of this compound cloud */
	UPROPERTY()
	TEnumAsByte<ECompound> type;

protected:
	/** The editable mesh for the compound cloud */
	UPROPERTY(BlueprintReadWrite, Category = "CELL|CELL_Compound")
	UProceduralMeshComponent * mesh;

	/** The vertexbuffer for the compound cloud */
	UPROPERTY(BlueprintReadWrite, Category = "CELL|CELL_Compound")
	TArray<FVector> vertices;

	/** The indexbuffer for the compound cloud */
	UPROPERTY(BlueprintReadWrite, Category = "CELL|CELL_Compound")
	TArray<int32> indices;

	/** Will point to the player as long as he/she is consuming the compound cloud; else nullptr*/
	UPROPERTY(BlueprintReadWrite, Category = "CELL|CELL_Compound")
	class ACharacter_SingleCelled* consumingPlayer;

	/** Will point to a cell as long as it is consuming the compound cloud; else nullptr 
	* No class for this so far so don't use it
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CELL|CELL_Compound")
	class AActor* consumingCell;
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	void CreateCube();

	/** Creates random mesh*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	void CreateCloudMesh(FMeshBounds _b);

	/** Reshapes the mesh away from the object that is consuming the cloud */
	UFUNCTION()
	void ReshapeMeshOnConsumption();

	UFUNCTION()
	void CloudFinishConsumption();

	/** Called every 5 seconds */
	UFUNCTION()
	void DespawnTick();
protected:
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Collision")
	void BeginOverlap(AActor* otherActor);

	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Collision")
	void EndOverlap(AActor* otherActor);

	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	ECompound GetType();

public:
	
};
