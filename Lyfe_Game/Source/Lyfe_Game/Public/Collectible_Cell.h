// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PassiveObject_Cell.h"
#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Collectible_Cell.generated.h"

UCLASS()
class LYFE_GAME_API ACollectible_Cell : public APassiveObject_Cell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible_Cell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
protected:
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	/** Whatever this specific collectible will do once it is collected */
	UFUNCTION()
	void WasCollected();
};
