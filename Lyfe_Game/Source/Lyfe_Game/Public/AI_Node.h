// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EConditionLeftSide : uint8
{
	EHealth,
	ENutrition,
	EAttacked,
	EEnemy
};

/**
 * 
 */
class LYFE_GAME_API AI_Node
{
public:
	AI_Node();
	~AI_Node();
};

class LYFE_GAME_API AI_DecisionNode : AI_Node
{
public:
	AI_DecisionNode();
	~AI_DecisionNode();
};

class LYFE_GAME_API AI_ActionNode : AI_Node
{
public:
	AI_ActionNode();
	~AI_ActionNode();
};