// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Character_SingleCelled.h"

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// PRIVATE ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void AGameMode_Cell::UpdateLowCompound()
{
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		TArray<bool> isLow = { 
			false, //carbon
			false, //nitrogen
			false, //oxygen
			false, //phosphor
			false  //sulfur
		};

		//cycle through all compounds and see if the are <= than 10% of their maximum
		//if they are set, their value in the array to true
		//after this is done:
		//check if maybe there are no compounds that are low
		//	in that case set lowCompound to ""
		//most likely that won't be the case so:
		//check what currently is in lowCompound
		//start at that value in the array and go to the next one that is low and set it


		//											current amount		/									maximum			<= 0.1f
		isLow[0] = ((float)controller->GetCompound("carbon", false)		/ (float)controller->GetCompound("carbon", true))	<= 0.1f;
		isLow[1] = ((float)controller->GetCompound("nitrogen", false)	/ (float)controller->GetCompound("nitrogen", true)) <= 0.1f;
		isLow[2] = ((float)controller->GetCompound("oxygen", false)		/ (float)controller->GetCompound("oxygen", true))	<= 0.1f;
		isLow[3] = ((float)controller->GetCompound("phosphor", false)	/ (float)controller->GetCompound("phosphor", true)) <= 0.1f;
		isLow[4] = ((float)controller->GetCompound("sulfur", false)		/ (float)controller->GetCompound("sulfur", true))	<= 0.1f;

		//UE_LOG(LogTemp, Warning, TEXT("carbon: %d"), isLow[0]);
		//UE_LOG(LogTemp, Warning, TEXT("nitrogen: %d"), isLow[1]);
		//UE_LOG(LogTemp, Warning, TEXT("oxygen: %d"), isLow[2]);
		//UE_LOG(LogTemp, Warning, TEXT("phosphor: %d"), isLow[3]);
		//UE_LOG(LogTemp, Warning, TEXT("sulfur: %d"), isLow[4]);

		if (!isLow[0] && !isLow[1] && !isLow[2] && !isLow[3] && !isLow[4])
		{
			lowCompound = "";
		}
		else
		{
			int start = 0;
			if (lowCompound.ToLower().Equals(""))
			{
				//this starts to look at carbon and moves on from there
				start = 0;
			}
			else if (lowCompound.ToLower().Equals("carbon"))
			{
				//this starts to look at nitrogen and moves on from there
				start = 1;
			}
			else if (lowCompound.ToLower().Equals("nitrogen"))
			{
				//this starts to look at oxygen and moves on from there
				start = 2;
			}
			else if (lowCompound.ToLower().Equals("oxygen"))
			{
				//this starts to look at phosphor and moves on from there
				start = 3;
			}
			else if (lowCompound.ToLower().Equals("phosphor"))
			{
				//this starts to look at sulfur and moves on from there
				start = 4;
			}
			else if (lowCompound.ToLower().Equals("sulfur"))
			{
				//this starts to look at carbon and moves on from there
				start = 0;
			}

			//6 so it can return to the starting position if there are not other compounds
			int position = 0;
			for (position; position < 6; position++)
			{
				if (isLow[(start + position) % 5])
				{
					break;
				}
			}

			switch ((start + position) % 5)
			{
			case 0:
				lowCompound = "Carbon";
				break;
			case 1:
				lowCompound = "Nitrogen";
				break;
			case 2:
				lowCompound = "Oxygen";
				break;
			case 3:
				lowCompound = "Phosphor";
				break;
			case 4:
				lowCompound = "Sulfur";
				break;
			default:
				lowCompound = "ERROR";
				break;
			}

		}

		controller->GetWorldTimerManager().SetTimer(lowCompoundRefreshTimer, this, &AGameMode_Cell::UpdateLowCompound, 2.f, false);
	}
}

void AGameMode_Cell::StartLowCompoundCycle()
{
	//ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (controller != nullptr)
	//{
	//	controller->GetWorldTimerManager().SetTimer(lowCompoundRefreshTimer, this, &AGameMode_Cell::UpdateLowCompound, 2.f, false);
	//}

	UpdateLowCompound();
}


  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// PUBLIC ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void AGameMode_Cell::SetControlSetting(EControlSettings newSetting)
{
	_eControlSetting = newSetting;
}

EControlSettings AGameMode_Cell::GetControlSetting()
{
	return _eControlSetting;
}

bool AGameMode_Cell::DisableWASDInput()
{
	return (_eControlSetting == EControlSettings::EFollowMouse);
}

FString AGameMode_Cell::GetLowCompound()
{
	return lowCompound;
}
