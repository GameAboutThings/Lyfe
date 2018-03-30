// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Meta_CellStage.generated.h"

#define CAMERA_DISTANCE 400.f
#define MOVEMENT_THRESHOLD 20.f
#define ROTATION_THRESHOLD 10.f
#define SPEED_BASE 10.f //input gets multiplied with this value before being defided by the cells weight

#define CONTROLSETTING EControlSettings::EFollowMouse

#define ZOOM_FACTOR 150.f //how far you zoom in our out with each time you scroll || PASST
#define ZOOM_SPEED 0.5f //how fast you zoom in or out
#define ZOOM_MIN_DISTANCE 300.f
#define ZOOM_MAX_DISTANCE 1500.f

#define CLOUD_MESH_VERTEX_DISTANCE_THRESHOLD 50.f
#define CLOUD_MESH_VERTEX_DELTA_MOVEMENT 5.f
#define CLOUD_CONSUMPTION_RATE 1.1f //How much of a cloud is consumed each frame
#define CLOUD_PLAYERROTATION_THRESHOLD 30.f //degree the player can face away from the compoud cloud for it to still move the vertices actievly away from him/her

UENUM()
enum class EPlayerState : uint8
{
	EDead,
	EAlive
};

UENUM(BlueprintType)
enum ECompound
{
	ECO2 UMETA(DisplayName = "CO2"),
	EO2 UMETA(DisplayName = "O2"),
	EAminoAcid UMETA(DisplayName = "AminoAcid"),
	EGlucose UMETA(DisplayName = "Glucose"),
	ELipid UMETA(DisplayName = "Lipid"),
	ENothing UMETA(DisplayName = "nothing")
};

UENUM()
enum class EControlSettings : uint8
{
	EFollowMouse,
	EWASD,
	EClick
};

UENUM()
enum class ESpawnable : uint8
{
	ECell UMETA(DisplayName = "Cell"),
	ECloud UMETA(DisplayName = "CompoundCloud"),
	EPassive UMETA(DisplayName = "PassiveObject")
};

/**
 * 
 */
UCLASS()
class LYFE_GAME_API UMeta_CellStage : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
