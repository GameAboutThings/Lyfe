// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsVolume_Cell.h"


void APhysicsVolume_Cell::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	bWaterVolume = true;
	FluidFriction = 1000.f;
}

