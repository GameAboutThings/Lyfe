// Fill out your copyright notice in the Description page of Project Settings.

#include "NonPlayer_Cell.h"
#include "AIController_Cell.h"


// Sets default values
ANonPlayer_Cell::ANonPlayer_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANonPlayer_Cell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANonPlayer_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANonPlayer_Cell::SetupMeta()
{
	_metaCell.currentHealth = 100.f;
	_metaCell.maxHealth = 100.f;
	_metaCell.movementSpeed = 40.f;
	_metaCell.rotationSpeed = 40.f;
	_metaCell.weight = 50.f;
}

