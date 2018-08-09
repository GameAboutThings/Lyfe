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

//+++++++++++++++++++++++++++++++++++++++++++ AI_SEXUALNODE +++++++++++++++++++++++++++++++

AI_SexualNode::AI_SexualNode(ESexuality sexuality, TArray<FString> partner)
{
	_eSexuality = sexuality;
	sexualPartner = partner;
}

AI_SexualNode::~AI_SexualNode()
{
}

void AI_SexualNode::Destroy()
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

AI_Node * AI_DecisionNode::GetLeftChild()
{
	if (leftChild == nullptr)
	{
		AI_Node* node = new AI_ActionNode(EAction::ENothing);

		leftChild = node;

		return node;
	}
	else
	{
		return leftChild;
	}
}

AI_Node * AI_DecisionNode::GetRightChild()
{
	if (rightChild == nullptr)
	{
		AI_Node* node = new AI_ActionNode(EAction::ENothing);

		rightChild = node;

		return node;
	}
	else
	{
		return rightChild;
	}
}

void AI_DecisionNode::Destroy()
{
	if(leftChild != nullptr)
		leftChild->Destroy();
	free(leftChild);

	if(rightChild != nullptr)
		rightChild->Destroy();
	free(rightChild);
}

//+++++++++++++++++++++++++++++++++++++++++++ AI_ACTIONNODE +++++++++++++++++++++++++++++++

AI_ActionNode::AI_ActionNode(EAction action)
{
	_eAction = action;
}

AI_ActionNode::~AI_ActionNode()
{
}

void AI_ActionNode::Destroy()
{
}

//+++++++++++++++++++++++++++++++++++++++++++ AI_BASENODE +++++++++++++++++++++++++++++++

AI_BaseNode::AI_BaseNode()
{
	
}

AI_BaseNode::~AI_BaseNode()
{
}

AI_Node * AI_BaseNode::GetIdleNode()
{
	if (idle == nullptr)
	{
		AI_Node*  node = new AI_ActionNode(EAction::ENothing);

		idle = node;

		return node;
	}
	else
	{
		return idle;
	}
}

AI_Node * AI_BaseNode::GetAttackedNode()
{
	if (attacked == nullptr)
	{
		AI_Node*  node = new AI_ActionNode(EAction::EFlee);

		attacked = node;

		return node;
	}
	else
	{
		return attacked;
	}
}

AI_Node * AI_BaseNode::GetLowHealthNode()
{
	if (lowHealth == nullptr)
	{
		AI_Node* node = new AI_ActionNode(EAction::EFlee);

		lowHealth = node;

		return node;
	}
	else
	{
		return lowHealth;
	}
}

AI_Node * AI_BaseNode::GetLowNutritionNode()
{
	if (lowNutrition == nullptr)
	{
		AI_Node* node = new AI_ActionNode(EAction::ESearchFood);

		lowNutrition = node;

		return node;
	}
	else
	{
		return lowNutrition;
	}
}

AI_Node * AI_BaseNode::GetNightNode()
{
	if (night == nullptr)
	{
		AI_Node* node = new AI_ActionNode(EAction::ESleep);

		night = node;

		return node;
	}
	else
	{
		return night;
	}
}

AI_SexualNode * AI_BaseNode::GetSexualityNode()
{
	if (sexuality == nullptr)
	{
		TArray<FString> partner;
		partner.Add("");
		AI_SexualNode* node = new AI_SexualNode(ESexuality::EAsexual, partner);

		sexuality = node;

		return node;
	}
	else
	{
		return sexuality;
	}
}

void AI_BaseNode::Destroy()
{
	if (idle != nullptr)
		idle->Destroy();
	free(idle);

	if (attacked != nullptr)
		attacked->Destroy();
	free(attacked);

	if (lowHealth != nullptr)
		lowHealth->Destroy();
	free(lowHealth);

	if (lowNutrition != nullptr)
		lowNutrition->Destroy();
	free(lowNutrition);

	if (night != nullptr)
		night->Destroy();
	free(night);

	if (sexuality != nullptr)
		sexuality->Destroy();
	free(sexuality);
}
