// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h";
#include <string>;

#define LANGUAGE_TYPES_COUNT 1;

/**
 * 
 */
class LYFE_GAME_API NG_Base
{
private: //variables
	//---- begin LANGUAGE TYPES
	//---- end LANGUAGE TYPES
public: //variables
private: //functions
	//---- begin LANGUAGE TYPES
	std::string LANGUAGE_TYPE_NORMAL(std::uint8_t index);
	std::string PickSyllable(std::uint8_t type);
public: //functions
	std::string GenerateName(std::uint16_t sylbCount, std::uint8_t type);
	std::string GenerateName(std::uint16_t sylbCount);
	NG_Base();
	~NG_Base();
};
