// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode_Cell.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Logging.h"
#include "Meta_CellStage.h"
//#include "CompoundStorageComponent_Cell.h"

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// PRIVATE ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


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

int AGameMode_Cell::GetPlayerSurroundings(ESpawnable objectType)
{
	if (objectType == ESpawnable::ECell)
	{
		return _playerSurroundings.cells;
	}
	else if (objectType == ESpawnable::ECloud)
	{
		return _playerSurroundings.clouds;
	}
	else if (objectType == ESpawnable::EPassive)
	{
		return _playerSurroundings.passives;
	}
	else
	{
		Logging::Log("Error while accessing count of spawned objects", true);
		return 0;
	}
}

void AGameMode_Cell::AddPlayerSurroundings(ESpawnable objectType, int number)
{
	if (objectType == ESpawnable::ECell)
	{
		_playerSurroundings.cells += number;
	}
	else if (objectType == ESpawnable::ECloud)
	{
		_playerSurroundings.clouds += number;
	}
	else if (objectType == ESpawnable::EPassive)
	{
		_playerSurroundings.passives += number;
	}
	else
	{
		Logging::Log("Error while adding to count of spawned objects", true);
	}
}
