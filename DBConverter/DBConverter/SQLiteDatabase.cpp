#include "stdafx.h"
#include "SQLiteDatabase.h"
#include "sqlite3.h"


SQLiteDatabase::SQLiteDatabase()
{
	m_sqliteDB = NULL;
}

SQLiteDatabase::~SQLiteDatabase()
{
	closeDb();
}

bool SQLiteDatabase::openDb(const char* pathName)
{
	int ret = sqlite3_open(pathName, &m_sqliteDB);
	return (ret == 0);
}
void SQLiteDatabase::closeDb()
{
	if (m_sqliteDB)
	{
		sqlite3_close(m_sqliteDB);
		m_sqliteDB = NULL;
	}
}
void SQLiteDatabase::executeQuery(const char* query, SQLiteDataStruct* data)
{
	if (data == NULL)
	{
		return;
	}
	char *zErrMsg = 0;
	int rc;

	/* Execute SQL statement */
	data->reset();
	rc = sqlite3_exec(m_sqliteDB, query, callback, data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Query successfully\n");
	}
}
//! This callback will be invoked per each row of result
int SQLiteDatabase::callback(void* userContext, int columnCount, char** results, char** fields)
{
	SQLiteDataStruct *data = static_cast<SQLiteDataStruct*> (userContext);
	if (data)
	{
		//get colName only once time
		if (data->columns.empty())
		{
			for (int i = 0; i < columnCount; i++)
			{
				data->columns.push_back(std::string(fields[i]));
			}
		}
		// Append record to the dataStruct
		std::vector<std::string> record;
		for (int i = 0; i < columnCount; i++)
		{
			record.push_back(std::string(results[i] ? results[i] : "NULL"));
		}
		data->data.push_back(record);
	}
	return 0;
}