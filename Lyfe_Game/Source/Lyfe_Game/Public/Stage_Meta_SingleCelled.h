// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define CAMERA_DISTANCE 400.f
#define MOVEMENT_THRESHOLD 20.f
#define ROTATION_THRESHOLD 10.f
#define SPEED_BASE 10.f //input gets multiplied with this value before being defided by the cells weight



#define ZOOM_FACTOR 150.f //how far you zoom in our out with each time you scroll || PASST
#define ZOOM_SPEED 0.5f //how fast you zoom in or out
#define ZOOM_MIN_DISTANCE 300.f
#define ZOOM_MAX_DISTANCE 1500.f

/**
 * 
 */
class LYFE_GAME_API Stage_Meta_SingleCelled
{
public:
	Stage_Meta_SingleCelled();
	~Stage_Meta_SingleCelled();
};
