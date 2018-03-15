// Fill out your copyright notice in the Description page of Project Settings.

#include "PassiveObject_Cell.h"


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
	
}

// Called every frame
void APassiveObject_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DecreaseMomentum();

}

//void APassiveObject_Cell::DecreaseMomentum()
//{
//	
//}

