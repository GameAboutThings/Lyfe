// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Meta_CellEditor.generated.h"

/* CAMERA MOVEMENT */
#define CAMERA_ZOOM_FACTOR 150.f //how far you zoom in our out with each time you scroll || PASST
#define CAMERA_ZOOM_SPEED 0.5f //how fast you zoom in or out
#define CAMERA_ZOOM_MIN_DISTANCE 300.f
#define CAMERA_ZOOM_MAX_DISTANCE 1500.f
#define CAMERA_START_DISTANCE 400.f

/* SCULPTING */
#define EDITOR_MAXNUM_NODES_PER_ARM 4
#define EDITOR_ARROW_DISTANCEFROMBASE 20.f
//#define EDITOR_ARROW_SCALE FVector(5.f)
#define EDITOR_NODE_SIZE_MIN 50.f
#define EDITOR_NODE_SIZE_MAX 150.f
#define EDITOR_NODE_DISTANCE 15.f


UENUM()
enum class ENodeType : uint8
{
	//Only the Editor Base has the base node. This can't be deleted.
	//Every third node can become a split node
	//Every other node is a normal node
	/*
	* Every node starts out as normal except for the base node obviously
	* When one node is split it becomes a split 
	* it's parent^2 and child^2 on the not split axis become a single
	* base is a special case it stays on that type
	* condition for split:
	* node is a normal not a single
	*/
	EBase UMETA(DisplayName = "Base"),
	ENormal UMETA(DisplayName = "Normal"),
	ESplit UMETA(DisplayName = "Split"),
	ESingle UMETA(DisplayName = "Single")
};

UENUM()
enum class EPosition : uint8
{
	EAbove UMETA(DisplayName = "above"),
	EBelow UMETA(DisplayName = "below"),
	ERight UMETA(DisplayName = "right"),
	ELeft UMETA(DisplayName = "left"),
	EBase UMETA(DisplayName = "base")
};

/**
 * 
 */
UCLASS()
class LYFE_GAME_API UMeta_CellEditor : public UObject
{
	GENERATED_BODY()
	
};
