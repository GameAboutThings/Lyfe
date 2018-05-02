// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Meta_CellStage.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Cell.generated.h"

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
	/** Used to store the count of all objects spawned on runtime */
	struct playerSurroundings
	{
		int cells;
		int clouds;
		int passives;
	};
public:


  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// VARIABLES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
private:
	/** The active control setting */
	EControlSettings _eControlSetting;
	
	playerSurroundings _playerSurroundings;

protected:
public:


  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:

protected:

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

	/** Returns the number of a chosen spawnable object */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Spawn")
	int GetPlayerSurroundings(ESpawnable objectType);

	/** Adds or reduces the count for one object type in the player's surroundings */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Spawn")
	void AddPlayerSurroundings(ESpawnable objectType, int number);
};
