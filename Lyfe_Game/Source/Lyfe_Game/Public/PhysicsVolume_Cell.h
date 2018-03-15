// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "PhysicsVolume_Cell.generated.h"

/**
 * 
 */
UCLASS()
class LYFE_GAME_API APhysicsVolume_Cell : public ADefaultPhysicsVolume
{
	GENERATED_BODY()

private:
	virtual void PostInitializeComponents() override;
};
