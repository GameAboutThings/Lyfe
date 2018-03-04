// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Cell.generated.h"

UENUM()
enum class EControlSettings : uint8
{
	EFollowMouse,
	EWASD
};

/**
 * 
 */
UCLASS()
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

public:


  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:

protected:
	/** Set the control setting
	* EFollowMouse -> Cell follows the cursor
	* EWASD		   -> Cell is moved with WASD
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL_Movement")
	void SetControlSetting(EControlSettings newSetting);

public:
	/** Returns the currently active control setting */
	UFUNCTION(BlueprintCallable, Category = "CELL_Movement")
	EControlSettings GetControlSetting();

	/** Returns whether the courser should be displayed or not */
	UFUNCTION(BlueprintCallable, Category = "CELL_GUI")
	bool DisableWASDInput();
	
};
