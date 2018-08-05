// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EConditionLeftSide : uint8
{
	ENothing,
	EHealth,
	ENutrition,
	EAttacked,
	EEnemy //used for enemy nearby or something
};

enum class EConditionMiddle : uint8
{
	EEmpty,
	EGreater,
	ESmaller,
	EEqual
};

enum class EConditionStem : uint8
{
	EIdle,
	EAttacked,
	ELowHealth,
	ELowNutrition,
	ENight
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

class LYFE_GAME_API AI_BaseNode : AI_Node
{
public:
	AI_BaseNode();
	~AI_BaseNode();
private:
	AI_Node * idle;
	AI_Node * attacked;
	AI_Node * lowHealth;
	AI_Node * lowNutrition;
	AI_Node * night;
public:
	void AddIdleNode();
};

class LYFE_GAME_API AI_DecisionNode : AI_Node
{
public:
	AI_DecisionNode();
	~AI_DecisionNode();

private:
	TEnumAsByte<EConditionLeftSide> _eLeftSide;
	TEnumAsByte<EConditionMiddle> _eMiddle;
	TEnumAsByte<EConditionStem> _eStem;

	AI_Node* leftChild;
	AI_Node* rightChild;

public:
	void MakeDecision(class AGameMode* gameMode);
};

class LYFE_GAME_API AI_ActionNode : AI_Node
{
public:
	AI_ActionNode();
	~AI_ActionNode();
};