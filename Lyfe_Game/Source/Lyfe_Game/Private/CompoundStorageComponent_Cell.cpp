// Fill out your copyright notice in the Description page of Project Settings.

#include "CompoundStorageComponent_Cell.h"
#include "Character_SingleCelled.h"
#include "Logging.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UCompoundStorageComponent_Cell::UCompoundStorageComponent_Cell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCompoundStorageComponent_Cell::BeginPlay()
{
	Super::BeginPlay();

	SetCompounds();

	StartLowCompoundCycle();
	lowCompound = "Carbon";

	_protein.maximum = 100;
	_protein.current = 25;
}


// Called every frame
void UCompoundStorageComponent_Cell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void UCompoundStorageComponent_Cell::EnforceCompoundBalance()
{
	AddCompound(_playerCompounds._CO2.balance, ECompound::ECO2);
	AddCompound(_playerCompounds._O2.balance, ECompound::EO2);
	AddCompound(_playerCompounds._AminoAcid.balance, ECompound::EAminoAcid);
	AddCompound(_playerCompounds._Glucose.balance, ECompound::EGlucose);
	AddCompound(_playerCompounds._Lipid.balance, ECompound::ELipid);

	//First of all set the volume back on the player
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(this->GetOwner());
	if (controller != nullptr)
	{

		controller->GetWorldTimerManager().SetTimer(consumptionTimer, this, &UCompoundStorageComponent_Cell::EnforceCompoundBalance, SURROUNDINGS_DELTA_TIME, false);
	}
}

FString UCompoundStorageComponent_Cell::GetCompoundName(ECompound compound)
{
	return FString();
}


void UCompoundStorageComponent_Cell::UpdateLowCompound()
{
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		TArray<bool> isLow = {
			false, //CO2
			false, //oxygen
			false, //amino acid
			false, //glucose
			false //lipid
		};

		//cycle through all compounds and see if the are <= than 10% of their maximum
		//if they are set, their value in the array to true
		//after this is done:
		//check if maybe there are no compounds that are low
		//	in that case set lowCompound to ""
		//most likely that won't be the case so:
		//check what currently is in lowCompound
		//start at that value in the array and go to the next one that is low and set it


		//											current amount										/									maximum											<= 0.1f
		isLow[0] = ((float)controller->GetCompoundStorage()->GetCompound(ECompound::ECO2, false) / (float)controller->GetCompoundStorage()->GetCompound(ECompound::ECO2, true)) <= 0.1f;
		isLow[1] = ((float)controller->GetCompoundStorage()->GetCompound(ECompound::EO2, false) / (float)controller->GetCompoundStorage()->GetCompound(ECompound::EO2, true)) <= 0.1f;
		isLow[2] = ((float)controller->GetCompoundStorage()->GetCompound(ECompound::EAminoAcid, false) / (float)controller->GetCompoundStorage()->GetCompound(ECompound::EAminoAcid, true)) <= 0.1f;
		isLow[3] = ((float)controller->GetCompoundStorage()->GetCompound(ECompound::EGlucose, false) / (float)controller->GetCompoundStorage()->GetCompound(ECompound::EGlucose, true)) <= 0.1f;
		isLow[4] = ((float)controller->GetCompoundStorage()->GetCompound(ECompound::ELipid, false) / (float)controller->GetCompoundStorage()->GetCompound(ECompound::ELipid, true)) <= 0.1f;

		if (!isLow[0] && !isLow[1] && !isLow[2] && !isLow[3] && !isLow[4])
		{
			lowCompound = "";
			_eLowCompound = ECompound::ENothing;
		}
		else
		{
			int start = 0;
			if (_eLowCompound == ECompound::ENothing)
			{
				start = 0;
			}
			else if (_eLowCompound == ECompound::ECO2)
			{
				start = 1;
			}
			else if (_eLowCompound == ECompound::EO2)
			{
				start = 2;
			}
			else if (_eLowCompound == ECompound::EAminoAcid)
			{
				start = 3;
			}
			else if (_eLowCompound == ECompound::EGlucose)
			{
				start = 4;
			}
			else if (_eLowCompound == ECompound::ELipid)
			{
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
				lowCompound = "CO2";
				_eLowCompound = ECompound::ECO2;
				break;
			case 1:
				lowCompound = "Oxygen";
				_eLowCompound = ECompound::EO2;
				break;
			case 2:
				lowCompound = "Amino Acids";
				_eLowCompound = ECompound::EAminoAcid;
				break;
			case 3:
				lowCompound = "Glucose";
				_eLowCompound = ECompound::EGlucose;
				break;
			case 4:
				lowCompound = "Lipids";
				_eLowCompound = ECompound::ELipid;
				break;
			default:
				_eLowCompound = ECompound::ENothing;
				lowCompound = "ERROR";
				break;
			}

		}

		controller->GetWorldTimerManager().SetTimer(lowCompoundRefreshTimer, this, &UCompoundStorageComponent_Cell::UpdateLowCompound, 2.f, false);
	}
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void UCompoundStorageComponent_Cell::StartLowCompoundCycle()
{
	//ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (controller != nullptr)
	//{
	//	controller->GetWorldTimerManager().SetTimer(lowCompoundRefreshTimer, this, &AGameMode_Cell::UpdateLowCompound, 2.f, false);
	//}

	UpdateLowCompound();
}
  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void UCompoundStorageComponent_Cell::SetCompounds()
{
	//CO2
	_playerCompounds._CO2.maximum = 10000.f;
	_playerCompounds._CO2.current = 10000.f;
	_playerCompounds._CO2.balance = 0;

	//Oxygen
	_playerCompounds._O2.maximum = 10000.f;
	_playerCompounds._O2.current = 10000.f;
	_playerCompounds._O2.balance = 0;

	//Amino Acid
	_playerCompounds._AminoAcid.maximum = 10000.f;
	_playerCompounds._AminoAcid.current = 10000.f;
	_playerCompounds._AminoAcid.balance = 0;

	//Glucose
	_playerCompounds._Glucose.maximum = 10000.f;
	_playerCompounds._Glucose.current = 10000.f;
	_playerCompounds._Glucose.balance = 0;

	//Lipid
	_playerCompounds._Lipid.maximum = 10000.f;
	_playerCompounds._Lipid.current = 10000.f;
	_playerCompounds._Lipid.balance = 0;
}

void UCompoundStorageComponent_Cell::AddCompound(int amount, ECompound compound)
{
	//find the right compound to add the amount
	if (compound == ECompound::ECO2)
	{
		Logging::Log(_playerCompounds._CO2.current);
		Logging::Log(amount);
		//add the amount
		_playerCompounds._CO2.current = _playerCompounds._CO2.current + amount;

		//check if it's greater than the maximum or smaller than 0 and correct that
		if (_playerCompounds._CO2.current > _playerCompounds._CO2.maximum)
		{
			_playerCompounds._CO2.current = _playerCompounds._CO2.maximum;
		}
		else if (_playerCompounds._CO2.current < 0)
		{
			_playerCompounds._CO2.current = 0;
		}
	}
	else if (compound == ECompound::EO2)
	{
		Logging::Log(_playerCompounds._O2.current);
		Logging::Log(amount);
		_playerCompounds._O2.current = _playerCompounds._O2.current + amount;

		if (_playerCompounds._O2.current > _playerCompounds._O2.maximum)
		{
			_playerCompounds._O2.current = _playerCompounds._O2.maximum;
		}
		else if (_playerCompounds._O2.current < 0)
		{
			_playerCompounds._O2.current = 0;
		}
	}
	else if (compound == ECompound::EAminoAcid)
	{
		Logging::Log(_playerCompounds._AminoAcid.current);
		Logging::Log(amount);
		_playerCompounds._AminoAcid.current = _playerCompounds._AminoAcid.current + amount;

		if (_playerCompounds._AminoAcid.current > _playerCompounds._AminoAcid.maximum)
		{
			_playerCompounds._AminoAcid.current = _playerCompounds._AminoAcid.maximum;
		}
		else if (_playerCompounds._AminoAcid.current < 0)
		{
			_playerCompounds._AminoAcid.current = 0;
		}
	}
	else if (compound == ECompound::EGlucose)
	{
		Logging::Log(_playerCompounds._Glucose.current);
		Logging::Log(amount);
		_playerCompounds._Glucose.current = _playerCompounds._Glucose.current + amount;

		if (_playerCompounds._Glucose.current > _playerCompounds._Glucose.maximum)
		{
			_playerCompounds._Glucose.current = _playerCompounds._Glucose.maximum;
		}
		else if (_playerCompounds._Glucose.current < 0)
		{
			_playerCompounds._Glucose.current = 0;
		}
	}
	else if (compound == ECompound::ELipid)
	{
		Logging::Log(_playerCompounds._Lipid.current);
		Logging::Log(amount);
		_playerCompounds._Lipid.current = _playerCompounds._Lipid.current + amount;

		if (_playerCompounds._Lipid.current > _playerCompounds._Lipid.maximum)
		{
			_playerCompounds._Lipid.current = _playerCompounds._Lipid.maximum;
		}
		else if (_playerCompounds._Lipid.current < 0)
		{
			_playerCompounds._Lipid.current = 0;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at AddCompound()"), *GetCompoundName(compound));
	}
}

int UCompoundStorageComponent_Cell::GetCompound(ECompound compound, bool bMax)
{
	if (bMax)
	{
		if (compound == ECompound::ECO2)
		{
			return _playerCompounds._CO2.maximum;
		}
		else if (compound == ECompound::EO2)
		{
			return _playerCompounds._O2.maximum;
		}
		else if (compound == ECompound::EAminoAcid)
		{
			return _playerCompounds._AminoAcid.maximum;
		}
		else if (compound == ECompound::EGlucose)
		{
			return _playerCompounds._Glucose.maximum;
		}
		else if (compound == ECompound::ELipid)
		{
			return _playerCompounds._Lipid.maximum;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompound()"), *GetCompoundName(compound));
			return 0;
		}
	}
	else
	{
		if (compound == ECompound::ECO2)
		{
			return _playerCompounds._CO2.current;
		}
		else if (compound == ECompound::EO2)
		{
			return _playerCompounds._O2.current;
		}
		else if (compound == ECompound::EAminoAcid)
		{
			return _playerCompounds._AminoAcid.current;
		}
		else if (compound == ECompound::EGlucose)
		{
			return _playerCompounds._Glucose.current;
		}
		else if (compound == ECompound::ELipid)
		{
			return _playerCompounds._Lipid.current;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompound()"), *GetCompoundName(compound));
			return 0;
		}
	}
}

int UCompoundStorageComponent_Cell::GetCompoundBalance(ECompound compound)
{
	if (compound == ECompound::ECO2)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._CO2.balance;
		}
	}
	else if (compound == ECompound::EO2)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._O2.balance;
		}
	}
	else if (compound == ECompound::EAminoAcid)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._AminoAcid.balance;
		}
	}
	else if (compound == ECompound::EGlucose)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._Glucose.balance;
		}
	}
	else if (compound == ECompound::ELipid)
	{
		if (GetCompound(compound, false) == 0)
		{
			return 0;
		}
		else
		{
			return _playerCompounds._Lipid.balance;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input compound <<%s>> not found at GetCompoundBalance()"), *GetCompoundName(compound));
		return 0;
	}
}

void UCompoundStorageComponent_Cell::AddProtein(int amount)
{
	_protein.current += amount;
	if (_protein.current > _protein.maximum)
	{
		_protein.current = _protein.maximum;
	}
	else if (_protein.current < 0)
	{
		_protein.current = 0;
	}
}

int UCompoundStorageComponent_Cell::GetProtein(bool bMax)
{
	if (bMax)
	{
		return _protein.maximum;
	}
	else
	{
		return _protein.current;
	}
}

FString UCompoundStorageComponent_Cell::GetLowCompound()
{
	return lowCompound;
}