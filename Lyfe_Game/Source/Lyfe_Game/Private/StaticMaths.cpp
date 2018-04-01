// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticMaths.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include <ctime>
#include <cstdlib>
#include "Logging.h"

StaticMaths::StaticMaths()
{
}

StaticMaths::~StaticMaths()
{
}

float StaticMaths::FindDeltaAngleDegrees(float A1, float A2)
{
	float delta = A2 - A1;

	if (delta > 180.0f)
	{
		delta = delta - 360.0f;
	}
	else if (delta < 180.0f)
	{
		delta = delta + 360.0f;
	}

	return delta;
}

bool StaticMaths::FindLookAtAngle2D(const FVector & start, const FVector & target, float & angle)
{
	FVector normal = (target - start).GetSafeNormal();

	if (!normal.IsNearlyZero())
	{
		angle = FMath::Atan2(start.Y, start.X) - FMath::Atan2(target.Y, target.X);
		angle = FMath::RadiansToDegrees(angle);
		return true;
	}

	return false;
}

FVector2D StaticMaths::ThreeDTo2D(const FVector & vector, EPlane plane)
{
	if (plane == EPlane::E_XY)
	{
		return FVector2D(vector.X, vector.Y);
	}
	else if (plane == EPlane::E_XZ)
	{
		return FVector2D(vector.X, vector.Z);
	}
	else if (plane == EPlane::E_YZ)
	{
		return FVector2D(vector.Y, vector.Z);
	}
	
	return FVector2D();
}

float StaticMaths::RR(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

FVector StaticMaths::WorldToLocal(const class AActor * referenceActor, const FVector & location)
{
	FTransform transform = referenceActor->GetTransform();
	FVector translation = transform.GetTranslation();
	return location - translation;
}

float StaticMaths::Distance2D(const FVector2D & a, const FVector2D & b)
{
	return FMath::Abs(FMath::Sqrt(FMath::Pow(a.X - b.X, 2) + FMath::Pow(a.Y - b.Y, 2)));
}

float StaticMaths::Distance2D(const FVector & a, const FVector & b)
{
	return StaticMaths::Distance2D(StaticMaths::ThreeDTo2D(a, EPlane::E_XY), StaticMaths::ThreeDTo2D(b, EPlane::E_XY));
}

FVector2D StaticMaths::Normalized2D(const FVector2D & a)
{
	float length = sqrt(pow(a.X, 2) + pow(a.Y, 2));
	return (a / length);
}

bool StaticMaths::RandomBool()
{
	//srand(time(0));
	int random = (int)(rand()) % 2;
	int random_2 = (int)(rand()) % 2;

	Logging::Log(random, true);

	return random_2 ? random : !random;
}
