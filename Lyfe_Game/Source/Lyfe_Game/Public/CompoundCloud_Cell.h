// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Compound_ParticleComponent_Cell.h"
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

	/** The vertexbuffer for the compound cloud */
	//UPROPERTY(BlueprintReadWrite, Category = "CELL|CompoundCloud|Mesh")
	//TArray<FVector> vertices;

	/** The indexbuffer for the compound cloud */
	//UPROPERTY(BlueprintReadWrite, Category = "CELL|CompoundCloud|Mesh")
	//TArray<int32> indices;

	/** Will point to the player as long as he/she is consuming the compound cloud; else nullptr*/
	//UPROPERTY(BlueprintReadWrite, Category = "CELL|CompoundCloud|Consumption")
	//class ACharacter_SingleCelled* consumingPlayer;

	/** Will point to a cell as long as it is consuming the compound cloud; else nullptr 
	* No class for this so far so don't use it
	*/
	//UPROPERTY(BlueprintReadWrite, Category = "CELL|CompoundCloud|Consumption")
	//class AActor* consumingCell;
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	void CreateCube();

	/** Creates random vertices and adds indices for them storing them in member variable vertices and indices*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Mesh")
	void CreateCloudVerticesAndIndices(FMeshBounds _b);

	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Mesh")
	void CreateCloudMesh();

	/** Reshapes the mesh away from the object that is consuming the cloud */
	UFUNCTION()
	void ReshapeMeshOnConsumption();

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

	/** Returns the type of the Compound Cloud as the Compound Enum*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CompoundCloud|Compound")
	ECompound GetType();
public:
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
};
