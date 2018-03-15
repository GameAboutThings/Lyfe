// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stage_Meta_SingleCelled.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Cell.generated.h"

UENUM()
enum class EControlSettings : uint8
{
	EFollowMouse,
	EWASD,
	EClick
};

/**
 * 
 */
UCLASS(Blueprintable)
class LYFE_GAME_API AGameMode_Cell : public AGameModeBase
{
	GENERATED_BODY()
	
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
	/** The active control setting */
	EControlSettings _eControlSetting;


protected:
	/** Will change every few frames */
	UPROPERTY(BlueprintReadWrite, Category = "CELL|CELL_Compound")
	FString lowCompound;

	FTimerHandle lowCompoundRefreshTimer;

public:


  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	void UpdateLowCompound();

protected:
	/** Called on BeginPlay(). Starts a Timer to get the next low compound every few seconds. */
	UFUNCTION(Blueprintcallable, Category = "CELL|CELL_Compound")
	void StartLowCompoundCycle();
public:
	/** Set the control setting
	* EFollowMouse -> Cell follows the cursor
	* EWASD		   -> Cell is moved with WASD
	* EClick	   -> Cell moves towards the position of the click
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	void SetControlSetting(EControlSettings newSetting);

	/** Returns the currently active control setting */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	EControlSettings GetControlSetting();

	/** Returns whether the courser should be displayed or not */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_GUI")
	bool DisableWASDInput();

	/** Returns one compound that is low at this moment. Used for display in the GUI*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	FString GetLowCompound();
};
