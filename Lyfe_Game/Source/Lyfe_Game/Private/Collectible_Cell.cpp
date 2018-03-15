// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible_Cell.h"


// Sets default values
ACollectible_Cell::ACollectible_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectible_Cell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectible_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectible_Cell::WasCollected()
{
}

