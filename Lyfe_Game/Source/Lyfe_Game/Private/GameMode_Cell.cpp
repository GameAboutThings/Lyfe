// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode_Cell.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// PRIVATE ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void AGameMode_Cell::UpdateLowCompound()
{
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		TArray<bool> isLow = { 
			false, //CO2
			false, //oxygen
			false, //amino acid
			false //glucose
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
		isLow[0] = ((float)controller->GetCompound(ECompound::ECO2, false)		/ (float)controller->GetCompound(ECompound::ECO2, true))	<= 0.1f;
		isLow[1] = ((float)controller->GetCompound(ECompound::EO2, false)	/ (float)controller->GetCompound(ECompound::EO2, true)) <= 0.1f;
		isLow[2] = ((float)controller->GetCompound(ECompound::EAminoAcid, false)		/ (float)controller->GetCompound(ECompound::EAminoAcid, true))	<= 0.1f;
		isLow[3] = ((float)controller->GetCompound(ECompound::EGlucose, false)	/ (float)controller->GetCompound(ECompound::EGlucose, true)) <= 0.1f;

		if (!isLow[0] && !isLow[1] && !isLow[2] && !isLow[3])
		{
			lowCompound = "";
		}
		else
		{
			int start = 0;
			if (_eLowCompound == ECompound::ENothing)
			{
				//this starts to look at carbon and moves on from there
				start = 0;
			}
			else if (_eLowCompound == ECompound::ECO2)
			{
				//this starts to look at nitrogen and moves on from there
				start = 1;
			}
			else if (_eLowCompound == ECompound::EO2)
			{
				//this starts to look at oxygen and moves on from there
				start = 2;
			}
			else if (_eLowCompound == ECompound::EAminoAcid)
			{
				//this starts to look at phosphor and moves on from there
				start = 3;
			}
			else if (_eLowCompound == ECompound::EGlucose)
			{
				//this starts to look at sulfur and moves on from there
				start = 4;
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
				lowCompound = "CO2";
				break;
			case 1:
				lowCompound = "Oxygen";
				break;
			case 2:
				lowCompound = "Amino Acids";
				break;
			case 3:
				lowCompound = "Glucose";
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
