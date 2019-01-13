#pragma once
#include<iostream>
#include "sqlite3.h"
#include "SQLiteDataStruct.h"

class SQLiteDatabase
{
public:
	SQLiteDatabase();
	~SQLiteDatabase();

	bool openDb(const char* pathName);
	void closeDb();
	void executeQuery(const char* query, SQLiteDataStruct* data);

	static int callback(void* userContext, int columnCount, char** results, char** fields); 
private:
	sqlite3* m_sqliteDB;
};