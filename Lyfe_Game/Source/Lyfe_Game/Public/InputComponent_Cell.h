// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Meta_CellStage.h"
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "InputComponent_Cell.generated.h"

/**
 * 
 */
UCLASS()
class LYFE_GAME_API UInputComponent_Cell : public UInputComponent
{
	GENERATED_BODY()


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
	EControlSettings _eControlSetting;

	/** targetLocation of previous frame */
	FVector targetLocation;

	/** targetLocation of previous frame */
	FVector targetLocationPrev;

	/** 1 if the player presses up or w
	* -1 if the player presses down or s
	* 0 for no input
	*/
	float forwardInput;

	/** 1 if the player presses right or d
	* -1 if the player presses left or a
	* 0 for no input
	*/
	float rightInput;

	bool bInteractGUI;

protected:
public:

  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	/** Returns target position for the cell to move towards */
	UFUNCTION()
	FVector GetTargetPosition();

	/** Transfer important params from the player cell to this component */
	UFUNCTION()
	void SetParams();

	/** Bound to the MoveForward Axis */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	void SetForwardMotion(float input);

	/** Bound to the MoveRight Axis */
	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	void SetRightMotion(float input);

	/** Called when the player clicks the left mouse button */
	void LeftClick();

	/** Called when the player clicks the right mouse button */
	void RightClick();

	void SetInteractGUI(bool input);

	bool GetInteractGUI();
	
};
