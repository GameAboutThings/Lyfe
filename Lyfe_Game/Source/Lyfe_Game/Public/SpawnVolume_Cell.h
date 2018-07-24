// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpawnVolume_Cell.generated.h"

USTRUCT(BlueprintType, Category = "CELL|CELL_Spawning")
struct FSpawnableObjects
{
	GENERATED_BODY()

	// Whenever anything is added in here also got to Spawn() and add it in the first if check
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CELL|CELL_Spawning")
	TSubclassOf<class APassiveObject_Cell> passive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CELL|CELL_Spawning")
	TSubclassOf<class ACompoundCloud_Cell> compoundCloud;
};

UCLASS()
class LYFE_GAME_API ASpawnVolume_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume_Cell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
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
	FTimerHandle spawnTimer;
protected:
	/** The bounds for the spawn volume */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CELL|CELL_Spawning")
	class UBoxComponent* volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CELL|CELL_Spawning")
	FSpawnableObjects _spawnableObjects;
public:
  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	/** Other than the normal tick this only runs every 1 second or so*/
	UFUNCTION()
	void SpawnTick();
protected:
	/** Spawns one randomly chosen object */
	UFUNCTION()
	void Spawn();
public:
	/** Returns the box component of the inner bounds */
	FORCEINLINE class UBoxComponent* GetVolume() const { return volume; };

	/** Returns a random point between the inner and outer volume*/
	UFUNCTION(BlueprintPure, Category = "CELL|CELL_Spawning")
	FVector GetRandomPointWithinBounds();
};
