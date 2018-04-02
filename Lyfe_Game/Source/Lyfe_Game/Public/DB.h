// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\SQLite\sqlite3.h"

#define DB_PATH "..\..\..\Content\Database\LYFE.db"

/**
 * 
 */
class LYFE_GAME_API DB
{
public:
	DB();
	~DB();

	/** Queries the database and returns the result 
	* @param query A valid SQL select on the database
	* @param result A pointer to the FString Array
	* @param timeout Timeout in milliseconds
	*
	* @return Boolean if the query was successful
	*/
	static bool Table(FString query, FString*** result, int timeout);
};
