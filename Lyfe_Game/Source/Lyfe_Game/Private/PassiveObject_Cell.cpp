// Fill out your copyright notice in the Description page of Project Settings.

#include "PassiveObject_Cell.h"
#include "Character_SingleCelled.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "StaticMaths.h"
#include "Logging.h"


// Sets default values
APassiveObject_Cell::APassiveObject_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APassiveObject_Cell::BeginPlay()
{
	Super::BeginPlay();

	SetActorEnableCollision(true);
	

	//First of all set the volume back on the player
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		controller->GetWorldTimerManager().SetTimer(despawnTimer, this, &APassiveObject_Cell::DespawnTick, 5.f, false);
	}
}

// Called every frame
void APassiveObject_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DecreaseMomentum();

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PRIVATE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void APassiveObject_Cell::DespawnTick()
{
	//First of all set the volume back on the player
	ACharacter_SingleCelled* controller = Cast<ACharacter_SingleCelled>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (controller != nullptr)
	{
		//check distance to player
		controller->GetActorLocation();
		this->GetActorLocation();

		float distance = StaticMaths::Distance2D(controller->GetActorLocation(), this->GetActorLocation());

		if (StaticMaths::Distance2D(controller->GetActorLocation(),
			this->GetActorLocation()) >= SURROUNDINGS_DESPAWN_DISTANCE)
		{
			this->Destroy();
		}
			

		controller->GetWorldTimerManager().SetTimer(despawnTimer, this, &APassiveObject_Cell::DespawnTick, 5.f, false);
	}
}

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////// PROTECTED ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////// PUBLIC /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

