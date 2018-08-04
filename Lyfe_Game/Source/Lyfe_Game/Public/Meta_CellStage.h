// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Meta_CellStage.generated.h"

/* MOVEMENT */
#define MOVEMENT_THRESHOLD 20.f
#define ROTATION_THRESHOLD 10.f
#define MOVEMENT_SPEED_BASE 10.f //input gets multiplied with this value before being defided by the cells weight

/* CONTROL SETTING FOR TESTING */
#define CONTROLSETTING EControlSettings::EWASD

/* CAMERA MOVEMENT */
#define CAMERA_ZOOM_FACTOR 150.f //how far you zoom in our out with each time you scroll || PASST
#define CAMERA_ZOOM_SPEED 0.5f //how fast you zoom in or out
#define CAMERA_ZOOM_MIN_DISTANCE 300.f
#define CAMERA_ZOOM_MAX_DISTANCE 1500.f
#define CAMERA_START_DISTANCE 400.f

/* COMPOUND CLOUDS */
#define CLOUD_MESH_VERTEX_DISTANCE_THRESHOLD 50.f
#define CLOUD_MESH_VERTEX_DELTA_MOVEMENT 5.f
#define CLOUD_MESH_CENTER_CELTA_MOVEMENT 50.f
#define CLOUD_CONSUMPTION_RATE 11.f //How much of a cloud is consumed each frame
#define CLOUD_PLAYERROTATION_THRESHOLD 30.f //degree the player can face away from the compoud cloud for it to still move the vertices actievly away from him/her
#define CLOUD_PARTICLE_MIN 30.f
#define CLOUD_PARTICLE_MAX 50.f
#define CLOUD_RADIUS 25.f
#define CLOUD_RADIUS_STEPS 15.f

/* SPAWNING AND DESPAWNING */
#define SURROUNDINGS_DESPAWN_DISTANCE 2000.f
#define SURROUNDINGS_MAX_CLOUD 10.f
#define SURROUNDINGS_MAX_PASSIVE 10.f
#define SURROUNDINGS_MAX_CELL 10.f
#define SURROUNDINGS_DELTA_TIME 5.f

UENUM()
enum class EPlayerState : uint8
{
	EDead UMETA(DisplayName = "Dead"),
	EAlive UMETA(DisplayName = "Alive")
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
	EFollowMouse UMETA(DisplayName = "FollowMouse"),
	EWASD UMETA(DisplayName = "WASD"),
	EClick UMETA(DisplayName = "Click")
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
