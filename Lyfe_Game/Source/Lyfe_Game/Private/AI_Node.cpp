// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Node.h"
#include "Logging.h"

//+++++++++++++++++++++++++++++++++++++++++++ AI_NODE +++++++++++++++++++++++++++++++

AI_Node::AI_Node()
{
}

AI_Node::~AI_Node()
{
}

//+++++++++++++++++++++++++++++++++++++++++++ AI_BASENODE +++++++++++++++++++++++++++++++

AI_BaseNode::AI_BaseNode()
{
}

AI_BaseNode::~AI_BaseNode()
{
}

//+++++++++++++++++++++++++++++++++++++++++++ AI_DECISIONNODE +++++++++++++++++++++++++++++++

AI_DecisionNode::AI_DecisionNode()
{
}

AI_DecisionNode::~AI_DecisionNode()
{
}

void AI_DecisionNode::MakeDecision(AGameMode * gameMode)
{
	switch (_eLeftSide)
	{
	case EConditionLeftSide::ENothing: 
	{ 
		//Put something like "Default()" in here
		//switch _eStem
		Logging::Log("MakeDecision.ENothing not implemented yet!", true); 
	}
		break;
	case EConditionLeftSide::EHealth: 
	{ 
		switch (_eMiddle)
		{
		case EConditionMiddle::EEmpty: { Logging::Log("MakeDecision.EHealth.EEmpty not implemented yet!", true); }
			break;
		case EConditionMiddle::EGreater: { Logging::Log("MakeDecision.EHealth.EGreater not implemented yet!", true); }
			break;
		case EConditionMiddle::ESmaller: { Logging::Log("MakeDecision.EHealth.ESmaller not implemented yet!", true); }
			break;
		case EConditionMiddle::EEqual: { Logging::Log("MakeDecision.EHealth.EEqual not implemented yet!", true); }
			break;
		}
	}
		break;
	case EConditionLeftSide::ENutrition: 
	{
		switch (_eMiddle)
		{
		case EConditionMiddle::EEmpty: { Logging::Log("MakeDecision.ENutrition.EEmpty not implemented yet!", true); }
			break;
		case EConditionMiddle::EGreater: { Logging::Log("MakeDecision.ENutrition.EGreater not implemented yet!", true); }
			break;
		case EConditionMiddle::ESmaller: { Logging::Log("MakeDecision.ENutrition.ESmaller not implemented yet!", true); }
			break;
		case EConditionMiddle::EEqual: { Logging::Log("MakeDecision.ENutrition.EEqual not implemented yet!", true); }
			break;
		}
	}
		break;
	case EConditionLeftSide::EAttacked: 
	{ 
		switch (_eMiddle)
		{
		case EConditionMiddle::EEmpty: { Logging::Log("MakeDecision.EAttacked.EEmpty not implemented yet!", true); }
			break;
		case EConditionMiddle::EGreater: { Logging::Log("MakeDecision.EAttacked.EGreater not implemented yet!", true); }
			break;
		case EConditionMiddle::ESmaller: { Logging::Log("MakeDecision.EAttacked.ESmaller not implemented yet!", true); }
			break;
		case EConditionMiddle::EEqual: { Logging::Log("MakeDecision.EAttacked.EEqual not implemented yet!", true); }
			break;
		}
	}
		break;
	case EConditionLeftSide::EEnemy: 
	{
		switch (_eMiddle)
		{
		case EConditionMiddle::EEmpty: { Logging::Log("MakeDecision.EEnemy.EEmpty not implemented yet!", true); }
			break;
		case EConditionMiddle::EGreater: { Logging::Log("MakeDecision.EEnemy.EGreater not implemented yet!", true); }
			break;
		case EConditionMiddle::ESmaller: { Logging::Log("MakeDecision.EEnemy.ESmaller not implemented yet!", true); }
			break;
		case EConditionMiddle::EEqual: { Logging::Log("MakeDecision.EEnemy.EEqual not implemented yet!", true); }
			break;
		}
	}
		break;
	}
}

//+++++++++++++++++++++++++++++++++++++++++++ AI_ACTIONNODE +++++++++++++++++++++++++++++++

AI_ActionNode::AI_ActionNode()
{
}

AI_ActionNode::~AI_ActionNode()
{
}
