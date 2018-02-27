// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stage_Meta_SingleCelled.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_SingleCelled.generated.h"

UCLASS()
class LYFE_GAME_API ACharacter_SingleCelled : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_SingleCelled();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FollowCourser();
	
};
