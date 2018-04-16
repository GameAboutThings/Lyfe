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
#define EDITOR_ARROW_DISTANCEFROMBASE 250.f
//#define EDITOR_ARROW_SCALE FVector(5.f)
#define EDITOR_NODE_SIZE_MIN 50.f
#define EDITOR_NODE_SIZE_MAX 150.f
#define EDITOR_NODE_DISTANCE 50.f


UENUM()
enum class ENodeType : uint8
{
	EBase UMETA(DisplayName = "Base"),
	ENormal UMETA(DisplayName = "Normal")
};

UENUM()
enum class EPosition : uint8
{
	EAbove UMETA(DisplayNAme = "above"),
	EBelow UMETA(DisplayNAme = "below"),
	ERight UMETA(DisplayNAme = "right"),
	ELeft UMETA(DisplayNAme = "left")
};

/**
 * 
 */
UCLASS()
class LYFE_GAME_API UMeta_CellEditor : public UObject
{
	GENERATED_BODY()

};
