// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Meta_CellStage.h"

//#define GetCurrentDirectory ""
#define LOG_DIRECTORY FString("/Lyfe/Logging") //Directory path
#define LOG_FILENAME FString("Lyfe_logFile.txt") //Filename
#define LOG_PATH FString(LOG_DIRECTORY + "/" + LOG_FILENAME) //path with filename

/**
 * 
 */
class LYFE_GAME_API Logging
{
public:
	Logging();
	~Logging();

	static void Log(FString inputString, bool bConsole);

	static void Log(FVector inputVector, bool bConsole);

	static void Log(FVector2D inputVector, bool bConsole);

	static void Log(float inputFloat, bool bConsole);

	static void Log(int inputInt, bool bConsole);

	static void Log(ECompound inputCompound, bool bConsole);
};
