// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
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
	/** The editable mesh for the compound cloud*/
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent * mesh;

	UPROPERTY()
	uint32 value;

protected:
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	/** Creates a single triangle on the mesh*/
	UFUNCTION(BlueprintCallable)
	void CreateTriangle();
protected:
public:
	
};
