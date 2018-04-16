// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Meta_CellEditor.h"
#include "CellEditor_NodeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYFE_GAME_API UCellEditor_NodeComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCellEditor_NodeComponent();

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
	/** If this node is a base node or just a regular one */
	UPROPERTY(VisibleAnywhere, Category = "CELL|Editor|Sculpting")
	ENodeType type;

	/** The basic sphere that will represent this component;
	* Might be replaced with static mesh later on but I'll try this for now
	*/
	UPROPERTY(VisibleAnywhere, Category = "CELL|Editor|Sculpting")
	class UStaticMeshComponent* sphereRepresentation;


	//Children of this node is the base node
	/** above */
	UPROPERTY()
	UCellEditor_NodeComponent* baseChild1;
	/** right */
	UPROPERTY()
	UCellEditor_NodeComponent* baseChild2;
	/** below */
	UPROPERTY()
	UCellEditor_NodeComponent* baseChild3;
	/** left */
	UPROPERTY()
	UCellEditor_NodeComponent* baseChild4;

	//The only child node if this is a normal node
	UPROPERTY()
	UCellEditor_NodeComponent* child;

public:
	/////////////////////////////////////////////////////////////////////////////
	////////////////////////////// FUNCTIONS ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	/** Set whether this node is of type normal or base */
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	void SetType(ENodeType newType);

	/** Returns the mesh component */
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	UStaticMeshComponent* GetMesh();

	/** Use this function only for baseNode; for normal nodes use withou position */
	UFUNCTION(Category = "CELL|Editor|Sculpting")
	void CreateAndAttachChildNode(EPosition position);

	UFUNCTION(Category = "CELL|Editor|Sculpting")
	void CreateAndAttachChildNode();

	/** Use this function only for baseNode; for normal nodes use withou position */
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	UCellEditor_NodeComponent* GetChild(EPosition, position);

	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	UCellEditor_NodeComponent* GetChild();
};
