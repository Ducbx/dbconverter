#pragma once
#include<iostream>
#include "sqlite3.h"
#include "SQLiteDataStruct.h"

class SQLiteDatabase
{
public:
	SQLiteDatabase();
	~SQLiteDatabase();

	bool openDb(char* pathName);
	bool closeDb();
	bool executeQuery(char* query, SQLiteDataStruct* data);

	static int callback(void* userContext, int columnCount, char** results, char** fields); 
private:
	sqlite3* m_sqliteDB;
};