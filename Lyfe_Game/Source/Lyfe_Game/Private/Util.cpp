// Fill out your copyright notice in the Description page of Project Settings.

#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

FString Util::EnumToString(ENodeType _eNodeType)
{
	FString ret = "";

	switch (_eNodeType)
	{
	case ENodeType::EBase:
		ret = "EBase";
		break;
	case ENodeType::ENormal:
		ret = "ENormal";
		break;
	case ENodeType::ESingle:
		ret = "ESingle";
		break;
	case ENodeType::ESplit:
		ret = "ESplit";
		break;
	default:
		ret = "-";
		break;
	}

	return ret;
}

FString Util::EnumToString(EPosition _ePosition)
{
	FString ret = "";

	switch (_ePosition)
	{
	case EPosition::EBase:
		ret = "EBase";
		break;
	case EPosition::EBelow:
		ret = "EBelow";
		break;
	case EPosition::ERight:
		ret = "ERight";
		break;
	case EPosition::ELeft:
		ret = "ELeft";
		break;
	case EPosition::EAbove:
		ret = "EAbove";
		break;
	default:
		ret = "-";
		break;
	}

	return ret;
}

FString Util::EnumToString(EPlayerState _eState)
{
	FString ret = "";

	switch (_eState)
	{
	case EPlayerState::EAlive:
		ret = "EAlive";
		break;
	case EPlayerState::EDead:
		ret = "EDead";
		break;
	default:
		ret = "-";
		break;
	}

	return ret;
}

FString Util::EnumToString(ECompound _eCompound)
{
	FString ret = "";

	switch (_eCompound)
	{
	case ECompound::ECO2:
		ret = "ECO2";
		break;
	case ECompound::EO2:
		ret = "EO2";
		break;
	case ECompound::EGlucose:
		ret = "EGlucose";
		break;
	case ECompound::ELipid:
		ret = "ELipid";
		break;
	case ECompound::EAminoAcid:
		ret = "EAminoAcid";
		break;
	case ECompound::ENothing:
		ret = "ENothing";
		break;
	default:
		ret = "-";
		break;
	}

	return ret;
}

FString Util::EnumToString(EControlSettings _eSetting)
{
	FString ret = "";

	switch (_eSetting)
	{
	case EControlSettings::EFollowMouse:
		ret = "EFollowMouse";
		break;
	case EControlSettings::EWASD:
		ret = "EWASD";
		break;
	case EControlSettings::EClick:
		ret = "EClick";
		break;
	default:
		ret = "-";
		break;
	}

	return ret;
}

FString Util::Vector3DToString(FVector vector)
{
	FString ret = "";
	ret.Append(FString::SanitizeFloat(vector.X));
	ret.Append("|");
	ret.Append(FString::SanitizeFloat(vector.Y));
	ret.Append("|");
	ret.Append(FString::SanitizeFloat(vector.Z));
	return ret;
}

FString Util::Vector2DToString(FVector2D vector)
{
	FString ret = "";
	ret.Append(FString::SanitizeFloat(vector.X));
	ret.Append("|");
	ret.Append(FString::SanitizeFloat(vector.Y));
	return ret;
}
