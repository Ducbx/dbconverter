#include "SQLiteDatabase.h"

SQLiteDatabase::SQLiteDatabase()
{
	m_sqliteDB = NULL;
}

SQLiteDatabase::~SQLiteDatabase()
{
	closeDb();
}

bool SQLiteDatabase::openDb(char* pathName)
{

}
bool SQLiteDatabase::closeDb()
{

}
bool SQLiteDatabase::executeQuery(char* query, SQLiteDataStruct* data)
{

}

int SQLiteDatabase::callback(void* userContext, int columnCount, char** results, char** fields)
{

}