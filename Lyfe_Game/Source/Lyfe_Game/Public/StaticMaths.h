// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EPlane
{
	E_XY,
	E_XZ,
	E_YZ
};

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

	static FVector2D ThreeDTo2D(const FVector & vector, EPlane plane);

	/** Returns a random float between a min and max*/
	static float RR(float min, float max);

	/** Used to compare positions of objects in world space to objects in local space; Ignores scale for now */
	static FVector WorldToLocal(const class AActor* referenceActor, const FVector & location);

	static float Distance2D(const FVector2D & a, const FVector2D & b);

	static float Distance2D(const FVector & a, const FVector & b);

	static FVector2D Normalized2D(const FVector2D & a);

	static FVector Normalized(const FVector & a);

	static bool RandomBool();

	/** Returns whether the given value lies between the other two */
	static bool Between(float value, float a, float b);

	/** 
	 * Adds the vertices, indices and normals for the sphere mesh around nodes in the cell editor
	 * @param latBands Number of latitude bands around the sphere
	 * @param longBands Number of longitude bands around the sphere
	 * @param radius Radius of the sphere
	 * @param centerOffset The relative location of the sphere center towards the editor-base
	 * @param vertices Pointer to the vertexBuffer
	 * @param normals Pointer to the normalBuffer
	 * @param indices Pointer to the indexBuffer
	*/
	static void AddSphereToCellMesh(int latBands, int longBands, int radius, FVector centerOffset, TArray<FVector>* vertices, TArray<FVector>* normals, TArry<int>* indices);
};
