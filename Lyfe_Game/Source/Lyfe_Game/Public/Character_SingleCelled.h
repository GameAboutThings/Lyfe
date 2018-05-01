// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Meta_CellStage.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_SingleCelled.generated.h"


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
	/** Saves all the values necessary for the player's movement */
	struct Movement
	{
		/** this will set the speed with which the cell will rotate towards the player's courser. => How many degrees per frame
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

		/** targetLocation of previous frame */
		FVector targetLocationPrev;
	};

	///** One single compound*/
	//struct Compound
	//{
	//	int current;
	//	int maximum;
	//	int balance;
	//};

	/** Saves all compunds within the player */
	//struct Compounds
	//{
	//	Compound _CO2;
	//	Compound _O2;
	//	Compound _AminoAcid;
	//	Compound _Glucose;
	//	Compound _Lipid;
	//};

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

	//UPROPERTY()
	//class USphereComponent* testMesh;

	/** The camera that follows your cell around */
	class UCameraComponent* playerCamera;

	/** The springarm the camera is attached to */
	class USpringArmComponent* cameraAttachmentArm;

	/** True when the player character is moving */
	bool bIsMoving;

	/** True when the player character is rotating */
	bool bIsRotating;

	/** stores all compounds for the player */
	//Compounds _playerCompounds;

	///** stores current and max Protein */
	//Compound _protein;

	/** Whether the mouse influences Gameplay or the GUI */
	bool bInteractGUI;

	/** A class that stores all compounds including proteins */
	class UCompoundStorageComponent_Cell* compoundStorage;

protected:
	UPROPERTY(BlueprintReadWrite)
	class UStaticMeshComponent* playerMesh;

public:
	/** The direction the player is facing */
	class UArrowComponent* playerDirection;


  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:

	/** Determines the location the cell will move towards 
	* For EFollowMouse it's the mouse position
	* For EWASD it's a vector determined through the user's key input
	*/
	void DetermineTargetLocation();

	void MoveToTargetLocation(float DeltaTime);

	void Die();

	/** Access the player Camera */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Camera")
	class UCameraComponent* GetPlayerCamera();

	/** Moves the camera closer to or further away from the player cell */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Camera")
	void Zoom(float input);

	/** Called when the player clicks the left mouse button */
	void OnLeftClick();

	/** Called when the player clicks the right mouse button */
	void OnRightClick();

	///** Sets compounds when world is loaded.
	//* Should not be called anywhere else.
	//*/
	//void SetCompounds();

	/** Sets whether the player interacts with the GUI or with the Game. This is mostly relevant for EFollowMouse*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_HUD")
	void SetInteractGUI(bool bGUI);

	/** Only used for key binding*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_HUD")
	void SetInteractGUITrue();

	///** Enforces the balance saved for every compound; Called every frame to reduce compound or rather metabolize it*/
	//void EnforceCompoundBalance();

	/*FString GetCompoundName(ECompound compound);*/

protected:
	/** Bound to the MoveForward Axis */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Movement")
	void SetForwardMotion(float input);

	/** Bound to the MoveRight Axis */
	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	void SetRightMotion(float input);

	/** Returns the cells rotation speed */
	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	float GetRotationSpeed();

	/** Returns the cells movement speed */
	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	float GetMovementSpeed();

	/** Returns the cell's maximum health */
	UFUNCTION(BlueprintCallable, Category = "CELL|Health")
	float GetMaxHealth();

public:
	/** Returns the cells wight
	* Public because this is also used to determine dominant cell for absorbing
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	float GetWeight();

	/** Returns the cell's current health */
	UFUNCTION(BlueprintCallable, Category = "CELL|Health")
	float GetCurrentHealth();

	/** Used to manipulate the cell's health 
	* @param amount can be positive or negative
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|Health")
	void AddHealth(float amount);

	/** Allows to set the state for the player */
	UFUNCTION(BlueprintCallable, Category = "CELL|State")
	void SetPlayerState(EPlayerState newState);

	/** Allows to acces the state of the player */
	UFUNCTION(BlueprintCallable, Category = "CELL|State")
	EPlayerState GetPlayerState();

	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	bool PlayerIsMoving();

	UFUNCTION(BlueprintCallable, Category = "CELL|Movement")
	UCompoundStorageComponent_Cell* GetCompoundStorage();
};
