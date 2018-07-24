// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Meta_CellStage.h"
//#include "Util.h"

#define LOG_DIRECTORY FString("/Lyfe/Logging") //Directory path
#define LOG_FILENAME FString("Lyfe_logFile.log") //Filename
#define LOG_PATH FString(LOG_DIRECTORY + "/" + LOG_FILENAME) //path with filename

/**
 * 
 */
class LYFE_GAME_API Logging
{
public:
	Logging();
	~Logging();

	//String
	static void Log(FString inputString, const char comment[], bool bConsole);

	static void Log(FString inputString, bool bConsole);

	static void Log(FString inputString);

	static void Log(FString inputString, const char comment[]);


	//char
	static void Log(const char inputString[], const char comment[], bool bConsole);

	static void Log(const char inputString[], bool bConsole);

	static void Log(const char inputString[]);

	static void Log(const char inputString[], const char comment[]);


	//Vector 3D
	static void Log(FVector inputVector, const char comment[], bool bConsole);

	static void Log(FVector inputVector, bool bConsole);

	static void Log(FVector inputVector);

	static void Log(FVector inputVector, const char comment[]);


	//Vector 2D
	static void Log(FVector2D inputVector, const char comment[], bool bConsole);

	static void Log(FVector2D inputVector, bool bConsole);

	static void Log(FVector2D inputVector);

	static void Log(FVector2D inputVector, const char comment[]);


	//Float
	static void Log(float inputFloat, const char comment[], bool bConsole);

	static void Log(float inputFloat, bool bConsole);

	static void Log(float inputFloat);

	static void Log(float inputFloat, const char comment[]);


	//Integer
	static void Log(int inputInt, const char comment[], bool bConsole);

	static void Log(int inputInt, bool bConsole);

	static void Log(int inputInt);

	static void Log(int inputInt, const char comment[]);


	//Compound
	static void Log(ECompound inputCompound, const char comment[], bool bConsole);

	static void Log(ECompound inputCompound, bool bConsole);

	static void Log(ECompound inputCompound);

	static void Log(ECompound inputCompound, const char comment[]);


	//Player State
	static void Log(EPlayerState inputState, const char comment[], bool bConsole);

	static void Log(EPlayerState inputState, bool bConsole);

	static void Log(EPlayerState inputState);

	static void Log(EPlayerState inputState, const char comment[]);


	//ControlSetting
	static void Log(EControlSettings inputControls, const char comment[], bool bConsole);

	static void Log(EControlSettings inputControls, bool bConsole);

	static void Log(EControlSettings inputControls);

	static void Log(EControlSettings inputControls, const char comment[]);
};
