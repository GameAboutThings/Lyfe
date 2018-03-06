// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stage_Meta_SingleCelled.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_SingleCelled.generated.h"

UENUM()
enum class EPlayerState : uint8
{
	EDead,
	EAlive
};

UCLASS()
class LYFE_GAME_API ACharacter_SingleCelled : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_SingleCelled();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/


  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////// CLASSES | STRUCTS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////
private:
	struct Movement
	{
		/** this will set the speed with which the cell will rotate towards the player's courser.
		* Can be called through code but not set.
		* It will be calculated through the parts on the player's cell.
		*/
		float rotationSpeed;

		/** This will set the speed with which the cell will move towards the player's courser.
		* Can be called through code but not set.
		* It will be calculated through the parts on the player's cell.
		*/
		float movementSpeed;

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

		/** The location the cell will move towards */
		FVector targetLocation;
	};

protected:

public:



  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// VARIABLES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
private:
	/** This variable describes all variables needed for movement calculation */
	Movement _movement;
	/** Sets the weight for the cell;
	* has influence on rotation and movement
	*/
	float weight;

	/** The maximum health the player cell can have currently .
	* Can be called through code but not set.
	* It will be calculated through the parts on the player's cell.
	*/
	float maxHealth;

	/** The maximum health the player cell can have currently .
	* Can be called and manipulated through code.
	*/
	float currentHealth;

	/** Current player state */
	EPlayerState _ePlayerState;

	UPROPERTY()
	class USphereComponent* testMesh;

	/** The camera that follows your cell around */
	class UCameraComponent* playerCamera;

	/** The springarm the camera is attached to */
	class USpringArmComponent* cameraAttachmentArm;

	/** True when the player character is moving */
	bool bIsMoving;

protected:

public:


  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:

	/** Determines the location the cell will move towards 
	* For EFollowMouse it's the mouse position
	* For EWASD it's a vector determined through the user's key input
	*/
	void DetermineTargetLocation();

	void MoveToTargetLocation();

	void Die();

	/** Access the player Camera */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Camera")
	class UCameraComponent* GetPlayerCamera();

	/** Bound to the MoveForward Axis */
	void SetForwardMotion(float input);

	/** Bound to the MoveRight Axis */
	void SetRightMotion(float input);

	/** Moves the camera closer to or further away from the player cell */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Camera")
	void Zoom(float input);

	/** Called when the player clicks the left mouse button */
	void OnLeftClick();

	/** Called when the player clicks the right mouse button */
	void OnRightClick();

protected:
	/** Returns the cells rotation speed */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	float GetRotationSpeed();

	/** Returns the cells movement speed */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	float GetMovementSpeed();

	/** Returns the cell's maximum health */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Health")
	float GetMaxHealth();

public:
	/** Returns the cells wight
	* Public because this is also used to determine dominant cell for absorbing
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	float GetWeight();

	/** Returns the cell's current health */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Health")
	float GetCurrentHealth();

	/** Used to manipulate the cell's health 
	* @param amount can be positive or negative
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Health")
	void AddHealth(float amount);

	/** Allows to set the state for the player */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_State")
	void SetPlayerState(EPlayerState newState);

	/** Allows to acces the state of the player */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_State")
	EPlayerState GetPlayerState();

	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	bool PlayerIsMoving();
};
