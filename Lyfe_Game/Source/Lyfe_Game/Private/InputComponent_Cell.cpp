// Fill out your copyright notice in the Description page of Project Settings.

#include "InputComponent_Cell.h"
#include "GameMode_Cell.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"

FVector UInputComponent_Cell::GetTargetPosition()
{
	targetLocationPrev = targetLocation;
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	ACharacter_SingleCelled* player = Cast<ACharacter_SingleCelled>(this->GetOwner());

	if (gameMode == nullptr)
		return FVector();

	if (player == nullptr)
		return FVector();

	
	FVector mouseDirection;
	//Check which control setting is activated
	if (gameMode->GetControlSetting() == EControlSettings::EFollowMouse) //Cell follows mouse
	{
		APlayerController* playerController = Cast<APlayerController>(player->GetController());
		if (playerController != nullptr)
		{
			playerController->DeprojectMousePositionToWorld(targetLocation, mouseDirection);
			targetLocation = targetLocation + (player->GetPlayerCameraArm()->TargetArmLength * mouseDirection);
		}
	}
	else if (gameMode->GetControlSetting() == EControlSettings::EWASD) //WASD to move
	{
		//This is handled in the Binding methods |||||||| for test reason not anymore

		targetLocation.X = (forwardInput * 1000.f) + player->GetActorLocation().X; //+ (_movement.targetLocationPrev.X / 100.f);
		targetLocation.Y = (rightInput * 1000.f) + player->GetActorLocation().Y; // + (_movement.targetLocationPrev.Y / 100.f);
	}
	else if (gameMode->GetControlSetting() == EControlSettings::EClick) //Cell moves towards location of mouse click
	{
		//This is handled in the on LeftClick method
	}

	if (targetLocation.Z != 0)
	{
		targetLocation.Z = 0;
	}

	return targetLocation;
}

void UInputComponent_Cell::SetParams()
{
}

void UInputComponent_Cell::SetForwardMotion(float input)
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		if (gameMode->GetControlSetting() == EControlSettings::EWASD)
		{
			forwardInput = FMath::Clamp(input, -1.f, 1.f) * 1.f;
		}
	}
}

void UInputComponent_Cell::SetRightMotion(float input)
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		if (gameMode->GetControlSetting() == EControlSettings::EWASD)
		{
			rightInput = FMath::Clamp(input, -1.f, 1.f) * 1.f;
		}
	}
}

void UInputComponent_Cell::LeftClick()
{
	AGameMode_Cell* gameMode = Cast<AGameMode_Cell>(GetWorld()->GetAuthGameMode());
	ACharacter_SingleCelled* player = Cast<ACharacter_SingleCelled>(this->GetOwner());

	if (gameMode == nullptr)
		return;

	if (player == nullptr)
		return;

	if (gameMode->GetControlSetting() == EControlSettings::EClick)
	{
		APlayerController* playerController = Cast<APlayerController>(player->GetController());
		if (playerController != nullptr)
		{
			FVector mouseDirection;

			playerController->DeprojectMousePositionToWorld(targetLocation, mouseDirection);
			targetLocation = targetLocation + (player->GetPlayerCameraArm()->TargetArmLength * mouseDirection);
		}
	}

	//return to the normal game
	bInteractGUI = false;
}

void UInputComponent_Cell::RightClick()
{
}

void UInputComponent_Cell::SetInteractGUI(bool input)
{
	bInteractGUI = input;
}

bool UInputComponent_Cell::GetInteractGUI()
{
	return bInteractGUI;
}
