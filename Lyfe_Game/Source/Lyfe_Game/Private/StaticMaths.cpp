// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticMaths.h"

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

FVector2D StaticMaths::ThreeDTo2D(const FVector & vector, FString plane)
{
	if (plane.Equals("XY"))
	{
		return FVector2D(vector.X, vector.Y);
	}
	else if (plane.Equals("XZ"))
	{
		return FVector2D(vector.X, vector.Z);
	}
	else if (plane.Equals("YZ"))
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
