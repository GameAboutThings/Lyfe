// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Meta_CellStage.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CompoundStorageComponent_Cell.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYFE_GAME_API UCompoundStorageComponent_Cell : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCompoundStorageComponent_Cell();

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
	/** One single compound*/
	struct FCompound
	{
		int current;
		int maximum;
		int balance;
	};

	/** Saves all compunds within the player */
	struct Compounds
	{
		FCompound _CO2;
		FCompound _O2;
		FCompound _AminoAcid;
		FCompound _Glucose;
		FCompound _Lipid;
	};
protected:
public:
  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// VARIABLES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
private:
	Compounds _playerCompounds;

	/** stores current and max Protein */
	FCompound _protein;

	FTimerHandle consumptionTimer;
protected:
public:
  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
	/** Enforces the balance saved for every compound; Called every frame to reduce compound or rather metabolize it*/
	UFUNCTION()
	void EnforceCompoundBalance();

	/** Returns name of compound enum */
	UFUNCTION()
	FString GetCompoundName(ECompound compound);
protected:
public:
	/** Sets compounds when world is loaded.
	* Should not be called anywhere else.
	*/
	UFUNCTION()
	void SetCompounds();

	/** Adds to or reduces a compound
	* It's up to the programmer to see if the compound is already 0. For debugging reasons it will be mentioned in the console, though.
	* @param amound Can be positive or negative
	* @param compound can be [carbon, oxygen, nitrogen, sulfur, phosphor]
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	void AddCompound(int amount, ECompound compound);

	/** Returns the amount left of that compound
	* @param amound Can be positive or negative
	* @param compound can be [carbon, oxygen, nitrogen, sulfur, phosphor]
	* @param bMax whether the maximum should be returned or the current; true => maximum
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	int GetCompound(ECompound compound, bool bMax);

	/** Returns the balance for the input compound; */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Compound")
	int GetCompoundBalance(ECompound compound);

	/** Allows the programmer to add or reduce Protein */
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Protein")
	void AddProtein(int amount);

	/** Allows the programmer to get the current Protein value
	* @param bMax whether the maximum should be returned or the current; true => maximum
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|CELL_Protein")
	int GetProtein(bool bMax);
};
