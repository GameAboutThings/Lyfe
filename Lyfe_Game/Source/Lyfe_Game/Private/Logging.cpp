// Fill out your copyright notice in the Description page of Project Settings.

#include "Logging.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/Misc/DateTime.h"

Logging::Logging()
{
}

Logging::~Logging()
{
}

void Logging::Log(FString inputString, bool bConsole)
{
	FDateTime date;
	FString log = "[ APPLICATIONTIME : ";
	log.Append(date.GetDate().ToString());
	log.Append(date.GetTimeOfDay().ToString());
	log.Append(" ] -> ");
	log.Append(inputString);
	log.Append("\r\n");
	
	IPlatformFile& logFile = FPlatformFileManager::Get().GetPlatformFile();

	//test id directory exists
	if (!logFile.DirectoryExists(*LOG_DIRECTORY))
	{
		UE_LOG(LogTemp, Warning, TEXT("*** Couldn't find log directory ***"));
		UE_LOG(LogTemp, Warning, TEXT("*** *** Trying to create log directory ..."));
		logFile.CreateDirectoryTree(*LOG_DIRECTORY);

		if (!logFile.DirectoryExists(*LOG_DIRECTORY))
		{
			UE_LOG(LogTemp, Warning, TEXT("*** Couldn't create log directory ***"));
			UE_LOG(LogTemp, Warning, TEXT("*** *** Cancelling ..."));
			return;
		}
	}

	//test file
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*LOG_PATH))
	{
		UE_LOG(LogTemp, Warning, TEXT("*** Couldn't find log file ***"));
		UE_LOG(LogTemp, Warning, TEXT("*** *** Trying to create log file ..."));
		FFileHelper::SaveStringToFile(log, *LOG_PATH);
		
		if(!FPlatformFileManager::Get().GetPlatformFile().FileExists(*LOG_PATH))
		{
			UE_LOG(LogTemp, Warning, TEXT("*** Couldn't create log file ***"));
			UE_LOG(LogTemp, Warning, TEXT("*** *** Trying to create log file ..."));
		}
	}
	else
	{
		FString oldLog;
		FFileHelper::LoadFileToString(oldLog, *LOG_PATH);
		oldLog.Append(log);
		FFileHelper::SaveStringToFile(oldLog, *LOG_PATH);
	}

	if (bConsole)
	{
		UE_LOG(LogTemp, Warning, TEXT("%c"), *inputString);
	}
}

void Logging::Log(FVector inputVector, bool bConsole)
{
	FString log = " VECTOR : { X: ";
	log.Append(FString::SanitizeFloat(inputVector.X));
	log.Append(" | Y: ");
	log.Append(FString::SanitizeFloat(inputVector.Y));
	log.Append(" | Z: ");
	log.Append(FString::SanitizeFloat(inputVector.Z));
	log.Append(" }");

	Log(log, bConsole);
}

void Logging::Log(FVector2D inputVector, bool bConsole)
{
	FString log = " VECTOR2D : { X: ";
	log.Append(FString::SanitizeFloat(inputVector.X));
	log.Append(" | Y: ");
	log.Append(FString::SanitizeFloat(inputVector.Y));
	log.Append(" }");

	Log(log, bConsole);
}

void Logging::Log(float inputFloat, bool bConsole)
{
	FString log = FString(" FLOAT : ").Append(FString::SanitizeFloat(inputFloat));
	Log(log, bConsole);
}

void Logging::Log(int inputInt, bool bConsole)
{
	FString log = FString(" INTEGER : ").Append(FString::SanitizeFloat(inputInt));
	Log(log, bConsole);
}

//void Logging::Log(bool inputBool, bool bConsole)
//{
//	FString log;
//	if (inputBool != 0 && inputBool != 1)
//	{
//		log = FString(inputBool);
//	}
//	else if (inputBool)
//	{
//		log.Append(" BOOLEAN : true");
//	}
//	else
//	{
//		log.Append(" BOOLEAN : false");
//	}
//
//	Log(log, bConsole);
//}
