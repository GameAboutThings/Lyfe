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


//String
void Logging::Log(FString inputString, const char comment[], bool bConsole)
{
	FDateTime date;
	FString log = "[ APPLICATIONTIME : ";
	log.Append(date.GetDate().ToString());
	log.Append(date.GetTimeOfDay().ToString());
	log.Append(" ] -> ");
	log.Append(FString(comment));
	log.Append(" ");
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

			if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*LOG_PATH))
			{
				UE_LOG(LogTemp, Warning, TEXT("*** *** *** Couldn't create log file ***"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("*** *** *** Log file created ***"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("*** *** *** Log file created ***"));
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

void Logging::Log(FString inputString, bool bConsole)
{
	Logging::Log(inputString, "", bConsole);
}

void Logging::Log(FString inputString)
{
	Logging::Log(inputString, false);
}

void Logging::Log(FString inputString, const char comment[])
{
	Logging::Log(inputString, comment, false);
}

//Char
void Logging::Log(const char inputString[], const char comment[], bool bConsole)
{
	Logging::Log(FString(inputString), comment, bConsole);
}

void Logging::Log(const char inputString[], bool bConsole)
{
	Logging::Log(inputString, "", bConsole);
}

void Logging::Log(const char inputString[])
{
	Logging::Log(inputString, false);
}

void Logging::Log(const char inputString[], const char comment[])
{
	Logging::Log(inputString, comment, false);
}


//Vector 3D
void Logging::Log(FVector inputVector, const char comment[], bool bConsole)
{
	FString log = " VECTOR : { X: ";
	log.Append(FString::SanitizeFloat(inputVector.X));
	log.Append(" | Y: ");
	log.Append(FString::SanitizeFloat(inputVector.Y));
	log.Append(" | Z: ");
	log.Append(FString::SanitizeFloat(inputVector.Z));
	log.Append(" }");

	Log(log, comment, bConsole);
}

void Logging::Log(FVector inputVector, bool bConsole)
{
	Logging::Log(inputVector, "", bConsole);
}

void Logging::Log(FVector inputVector)
{
	Logging::Log(inputVector, false);
}

void Logging::Log(FVector inputVector, const char comment[])
{
	Logging::Log(inputVector, comment, false);
}


//Vector 2D
void Logging::Log(FVector2D inputVector, const char comment[], bool bConsole)
{
	FString log = " VECTOR2D : { X: ";
	log.Append(FString::SanitizeFloat(inputVector.X));
	log.Append(" | Y: ");
	log.Append(FString::SanitizeFloat(inputVector.Y));
	log.Append(" }");

	Logging::Log(log, comment, bConsole);
}

void Logging::Log(FVector2D inputVector, bool bConsole)
{
	Logging::Log(inputVector, "", bConsole);
}

void Logging::Log(FVector2D inputVector)
{
	Logging::Log(inputVector, false);
}

void Logging::Log(FVector2D inputVector, const char comment[])
{
	Logging::Log(inputVector, comment, false);
}


//Float
void Logging::Log(float inputFloat, const char comment[], bool bConsole)
{
	FString log = FString(" FLOAT : ").Append(FString::SanitizeFloat(inputFloat));
	Logging::Log(log, comment, bConsole);
}

void Logging::Log(float inputFloat, bool bConsole)
{
	Logging::Log(inputFloat, "", bConsole);
}

void Logging::Log(float inputFloat)
{
	Logging::Log(inputFloat, false);
}

void Logging::Log(float inputFloat, const char comment[])
{
	Logging::Log(inputFloat, comment, false);
}


//Integer
void Logging::Log(int inputInt, const char comment[], bool bConsole)
{
	FString log = FString(" INTEGER : ").Append(FString::SanitizeFloat(inputInt));
	Log(log, comment, bConsole);
}

void Logging::Log(int inputInt, bool bConsole)
{
	Log(inputInt, "", bConsole);
}

void Logging::Log(int inputInt)
{
	Logging::Log(inputInt, false);
}

void Logging::Log(int inputInt, const char comment[])
{
	Logging::Log(inputInt, comment, false);
}

//Compound
void Logging::Log(ECompound inputCompound, const char comment[], bool bConsole)
{
	FString log = FString(" ECOMPOUND : ");
	switch (inputCompound)
	{
	case ECompound::EO2:
		log.Append(" O2 ");
		break;
	case ECompound::ECO2:
		log.Append(" CO2 ");
		break;
	case ECompound::EAminoAcid:
		log.Append(" Amino Acid ");
		break;
	case ECompound::EGlucose:
		log.Append(" Glucose ");
		break;
	case ECompound::ELipid:
		log.Append(" Lipid ");
		break;
	case ECompound::ENothing:
		log.Append(" Nothing ");
		break;
	}
	Logging::Log(log, comment, bConsole);
}

void Logging::Log(ECompound inputCompound, bool bConsole)
{
	Logging::Log(inputCompound, "", bConsole);
}

void Logging::Log(ECompound inputCompound)
{
	Logging::Log(inputCompound, false);
}

void Logging::Log(ECompound inputCompound, const char comment[])
{
	Logging::Log(inputCompound, comment, false);
}

//Player State
void Logging::Log(EPlayerState inputState, const char comment[], bool bConsole)
{
	FString log = FString(" EPLAYERSTATE : ");
	switch (inputState)
	{
	case EPlayerState::EDead:
		log.Append(" Dead ");
		break;
	case EPlayerState::EAlive:
		log.Append(" Alive ");
		break;
	}
	Logging::Log(log, comment, bConsole);
}

void Logging::Log(EPlayerState inputState, bool bConsole)
{
	Logging::Log(inputState, "", bConsole);
}

void Logging::Log(EPlayerState inputState)
{
	Logging::Log(inputState, false);
}

void Logging::Log(EPlayerState inputState, const char comment[])
{
	Logging::Log(inputState, comment, false);
}

//Control Setting
void Logging::Log(EControlSettings inputControls, const char comment[], bool bConsole)
{
	FString log = FString(" ECONTROLSETTING : ");
	switch (inputControls)
	{
	case EControlSettings::EFollowMouse:
		log.Append(" FollowMouse ");
		break;
	case EControlSettings::EWASD:
		log.Append(" WASD ");
		break;
	case EControlSettings::EClick:
		log.Append(" Click ");
		break;
	}
	Logging::Log(log, bConsole);
}

void Logging::Log(EControlSettings inputControls, bool bConsole)
{
	Logging::Log(inputControls, "", bConsole);
}

void Logging::Log(EControlSettings inputControls)
{
	Logging::Log(inputControls, false);
}

void Logging::Log(EControlSettings inputControls, const char comment[])
{
	Logging::Log(inputControls, comment, false);
}
