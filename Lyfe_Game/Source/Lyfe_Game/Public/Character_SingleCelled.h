// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Stage_Meta_SingleCelled.h"
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

	EPlayerState _ePlayerState;

protected:

public:


  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	void FollowCourser();

	void Die();

protected:
	/** Returns the cells rotation speed */
	UFUNCTION(BlueprintCallable, Category = "CELL_Movement")
	float GetRotationSpeed();

	/** Returns the cells movement speed */
	UFUNCTION(BlueprintCallable, Category = "CELL_Movement")
	float GetMovementSpeed();

	/** Returns the cell's maximum health */
	UFUNCTION(BlueprintCallable, Category = "CELL_Health")
	float GetMaxHealth();

public:
	/** Returns the cells wight
	* Public because this is also used to determine dominant cell for absorbing
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL_Movement")
	float GetWeight();

	/** Returns the cell's current health */
	UFUNCTION(BlueprintCallable, Category = "CELL_Health")
	float GetCurrentHealth();

	/** Used to manipulate the cell's health 
	* @param amount can be positive or negative
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL_Health")
	void AddHealth(float amount);

	/** Allows to set the state for the player */
	UFUNCTION(BlueprintCallable, Category = "CELL_State")
	void SetPlayerState(EPlayerState newState);

	/** Allows to acces the state of the player */
	UFUNCTION(BlueprintCallable, Category = "CELL_State")
	EPlayerState GetPlayerState();
};
