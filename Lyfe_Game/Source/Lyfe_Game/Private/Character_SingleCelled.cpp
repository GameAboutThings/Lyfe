// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_SingleCelled.h"


// Sets default values
ACharacter_SingleCelled::ACharacter_SingleCelled()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacter_SingleCelled::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_SingleCelled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_SingleCelled::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacter_SingleCelled::FollowCourser()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController != nullptr)
	{
		float x = 0;
		float y = 0;
		FVector mousePosition = FVector(0, 0, 0);

		//getting courser position on relation to world
		playerController->GetMousePosition(x, y);
		FVector screenPos = FVector(x, y, 0);
		playerController->DeprojectMousePositionToWorld(screenPos, mousePosition);

		//getting player position
		FVector currentPosition = GetActorLocation();

		//determining distance
		FVector toMouse = FVector(mousePosition.X - currentPosition.X, mousePosition.Y - currentPosition.Y, 0);
		float distance = sqrt(pow(toMouse.X, 2) + pow(toMouse.Y, 2));

		//how far to rotate
		float deg = 0;

		if (distance >= MOVEMENT_THRESHOLD)
		{
			
		}
		else if (deg >= ROTATION_THRESHOLD)
		{
			
		}
	}
}

