// Fill out your copyright notice in the Description page of Project Settings.

#include "DB.h"
#include "Logging.h"

DB::DB()
{
}

DB::~DB()
{
}

bool DB::Table(FString query, FString *** result, int timeout)
{
	sqlite3 *db;
	char* zErrMsg = 0;
	int rc;

	rc = sqlite3_open(DB_PATH, &db);

	if (rc)
	{
		FString errMsg = "*** Could not open Database : ";
		errMsg.Append(sqlite3_errmsg(db));

		Logging::Log(errMsg, false);
		return false;
	}
	else //managed to open db
	{
		Logging::Log("*** Opened Database ***", false);
	}

	sqlite3_close(db);

	return false; //REMOVE
}
