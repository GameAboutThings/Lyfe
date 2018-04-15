// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CellEditor_ArrowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYFE_GAME_API UCellEditor_ArrowComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCellEditor_ArrowComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/


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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CELL|Editor|Sculpting")
	class UStaticMeshComponent* arrowRepresentation;
public:
  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	UStaticMeshComponent* GetMeshComponent();
};
