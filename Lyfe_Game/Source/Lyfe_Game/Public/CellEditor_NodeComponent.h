// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Meta_CellEditor.h"
#include "CellEditor_NodeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYFE_GAME_API UCellEditor_NodeComponent : public UStaticMeshComponent
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
	ENodeType _eType;

	/** The position of the node relative to the parent 
	*	  O above
	*	<-O-> 
	*	  O below
	*	  O O right
	*/
	UPROPERTY()
	EPosition _ePositionToParent;

	/** The basic sphere that will represent this component;
	* Might be replaced with static mesh later on but I'll try this for now
	*/
	UPROPERTY(VisibleAnywhere, Category = "CELL|Editor|Sculpting")
	class UStaticMesh* sphereRepresentation;


	//Children of this node is the base node
	/** above */
	UPROPERTY()
	UCellEditor_NodeComponent* child1;
	/** right */
	UPROPERTY()
	UCellEditor_NodeComponent* child2;
	/** below */
	UPROPERTY()
	UCellEditor_NodeComponent* child3;
	/** left */
	UPROPERTY()
	UCellEditor_NodeComponent* child4;

public:
	UPROPERTY(/*EditAnywhere, BlueprintReadWrite, Category = "CELL|Editor|Sculpting"*/)
	class UCellEditor_ArrowComponent* arrowUp;

	UPROPERTY(/*EditAnywhere, BlueprintReadWrite, Category = "CELL|Editor|Sculpting"*/)
	class UCellEditor_ArrowComponent* arrowDown;

	UPROPERTY(/*EditAnywhere, BlueprintReadWrite, Category = "CELL|Editor|Sculpting"*/)
	class UCellEditor_ArrowComponent* arrowLeft;

	UPROPERTY(/*EditAnywhere, BlueprintReadWrite, Category = "CELL|Editor|Sculpting"*/)
	class UCellEditor_ArrowComponent* arrowRight;

	/////////////////////////////////////////////////////////////////////////////
	////////////////////////////// FUNCTIONS ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	/** Call this after creating a new node 
	* Will set all necessary member variables and assign a material
	*
	* @param _eNewType The type of node you created; Most likely normal
	* @param _eNewPositionToParent Where this node is relative to its parent
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	void PostConstructor(ENodeType _eNewType, EPosition _eNewPositionToParent);

	/** Set whether this node is of type normal or base */
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	ENodeType GetType();

	/** Returns the mesh component */
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	UStaticMesh* GetMesh();

	/** Use this function to create a child node at position
	*	  O This node would be a child at position above for it's parent
	*	  O
	*	<-O->
	* You need to factor in the position of the node who's child you want to create
	* Maybe use GetPositionToParent beforehand
	*/
	UFUNCTION(Category = "CELL|Editor|Sculpting")
	void CreateAndAttachChildNode(EPosition position);

	/** Use this function to return the child node at position
	*	  O This node would be a child at position above for it's parent
	*	  O
	*	<-O->
	* You need to factor in the position of the node who's child you want
	* Maybe use GetChildrenPositions beforehand
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	UCellEditor_NodeComponent* GetChild(EPosition position);

	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	TArray<EPosition> GetChildrenPositions();

	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	EPosition GetPositionToParent();

	/** Might come in Handy when moving a node too far around its parent so it turns from below to left or something 
	* This position applies only to the pointer not the actual position in 3D space
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	void SwitchNodePosition(EPosition _eTargetPosition);

	UFUNCTION()
	void SetType(ENodeType _eNewType);

	/** This doesn't create a new node; this is simply used to assign a node to the child pointer*/
	UFUNCTION()
	void SetChildNode(EPosition _ePosition, UCellEditor_NodeComponent* node);
};
