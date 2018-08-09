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

enum class ESexuality : uint8
{
	ESexual,
	EAsexual,
	EFlexible
};

enum class EAction : uint8
{
	ENothing,
	EFlee,
	EAttack,
	EEat,
	ESearchFood,
	ESleep
};

/**
 * 
 */
class LYFE_GAME_API AI_Node
{
public:
	AI_Node();
	~AI_Node();
	virtual void Destroy() {};
};

class LYFE_GAME_API AI_SexualNode : public AI_Node
{
public:
	AI_SexualNode(ESexuality sexuality, TArray<FString> partner);
	~AI_SexualNode();
private:
	TEnumAsByte<ESexuality> _eSexuality;
	TArray<FString> sexualPartner; //under no circumstances keep this a string
public:
	virtual void Destroy() override;
};

class LYFE_GAME_API AI_DecisionNode : public AI_Node
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

	AI_Node * GetLeftChild();
	AI_Node * GetRightChild();

	virtual void Destroy() override;
};

class LYFE_GAME_API AI_ActionNode : public AI_Node
{
public:
	AI_ActionNode(EAction action);
	~AI_ActionNode();

private:
	TEnumAsByte<EAction> _eAction;

public:
	virtual void Destroy() override;
};

class LYFE_GAME_API AI_BaseNode : public AI_Node
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
	AI_SexualNode * sexuality;
	
public:
	AI_Node * GetIdleNode();
	AI_Node * GetAttackedNode();
	AI_Node * GetLowHealthNode();
	AI_Node * GetLowNutritionNode();
	AI_Node * GetNightNode();
	AI_SexualNode* GetSexualityNode();
	void Destroy();
};