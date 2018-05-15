// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Meta_CellEditor.h"
#include "Meta_CellStage.h"

/**
 * 
 */
class LYFE_GAME_API Util
{
public:
	Util();
	~Util();

	static FString EnumToString(ENodeType _eNodeType);

	static FString EnumToString(EPosition _ePosition);

	static FString EnumToString(EPlayerState _eState);

	static FString EnumToString(ECompound _eCompound);

	static FString EnumToString(EControlSettings _eSetting);

	static FString Vector3DToString(FVector vector);

	static FString Vector2DToString(FVector2D vector);
};
