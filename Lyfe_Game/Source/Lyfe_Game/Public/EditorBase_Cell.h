// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EditorBase_Cell.generated.h"

UCLASS()
class LYFE_GAME_API AEditorBase_Cell : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEditorBase_Cell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
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
	int idCounter;
protected:
	/** The root of the node system that will form the sculpting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CELL|Editor|Sculpting")
	class UCellEditor_NodeComponent* baseNode;

	/** The camera that follows your cell around */
	UPROPERTY(BlueprintReadWrite, Category = "CELL|Editor|Camera")
	class UCameraComponent* camera;

	/** The springarm the camera is attached to */
	UPROPERTY(BlueprintReadWrite, Category = "CELL|Editor|Camera")
	class USpringArmComponent* cameraAttachmentArm;

	/** The mesh that basically represents the body of your cell */
	UPROPERTY(VisibleAnywhere, Category = "CELL|Editor|Sculpting")
	class UProceduralMeshComponent* bodyMesh;
public:
  /////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
private:
protected:
public:
	/** Generates the body mesh of the cell 
	 * Expand this method if EDITOR_MAXNUM_NODES_PER_ARM in Meta_CellEditor changes
	*/
	UFUNCTION(BlueprintCallable, Category = "CELL|Editor|Sculpting")
	void GenerateBodyMesh();

	UFUNCTION()
	int GetIdCounter();
};
