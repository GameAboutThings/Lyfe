// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LYFE_GAME_API StaticMaths
{
public:
	StaticMaths();
	~StaticMaths();

	/** Returns the delta angle between to angles */
	static float FindDeltaAngleDegrees(float A1, float A2);
	
	/** Determines Angle between two vectors
	* @param start Starting vector
	* @param target Target vector
	* @param angle The resulting angle
	*
	* @return True if the angle can be calculated
	*/
	static bool FindLookAtAngle2D(const FVector & start, const FVector & target, float & angle);

	static FVector2D ThreeDTo2D(const FVector & vector, FString plane);

	/** Returns a random float between a min and max*/
	static float RR(float min, float max);
};
