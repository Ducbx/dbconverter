#include "stdafx.h"
#include "SQLiteReader.h"
#include "SQLiteDatabase.h"

SQLiteReader::SQLiteReader()
{
}


SQLiteReader::~SQLiteReader()
{
}

//Get all table and table's form info
bool SQLiteReader::readStructure(const char* path, DatabaseStruct& data_info)
{
	//open database to get info
	SQLiteDatabase *sqlite = new SQLiteDatabase();
	if (!sqlite->openDb(path))
	{
		std::cout << "False to open SQLite DB";
		return false;
	}

	//get table name
	SQLiteDataStruct *tableNames = new SQLiteDataStruct();
	sqlite->executeQuery("SELECT name FROM sqlite_master WHERE type='table';", tableNames);
	//Why not using this query get from tableNames's sql "CREATE TABLE DeviceTable(id INTEGER PRIMARY KEY, active BOOLEAN, plcIp TEXT, plcPort TEXT, subscriber_key TEXT)"

	// with each table name, get info of all fields
	for (size_t i = 0; i < tableNames->data.size(); i++)
	{
		Table *std_table = new Table();											//push info to data struct format
		std_table->name = tableNames->data[i][1];								//push info to data struct format

		SQLiteDataStruct* sqliteFields = new SQLiteDataStruct();
		std::string str = "PRAGMA table_info('" + tableNames->data[i][1] + "');";
		const char *cstr = str.c_str();								
		sqlite->executeQuery(cstr, sqliteFields);

		struct SqliteTableField
		{
			std::string name;
			std::string type;
			int notnull;
			bool isPrimaryKey;
			void* defaultValue;
		};
		std::vector<SqliteTableField*> tableFields;
		// extract tablefield from fields
		for (int row = 0; row<sqliteFields->data.size(); row++)
		{
			Field* std_field = new Field();										//push info to data struct format
			std::string *field;
			SqliteTableField* tblField = new SqliteTableField();
			for (int col = 0; col<sqliteFields->data[row].size(); col++)
			{
				std::string& colName = sqliteFields->fields[col];
				std::string& value = sqliteFields->data[row][col];
				if (colName == "name")
				{
					tblField->name = value;
					std_field->name = value;
				}
				if (colName == "type")
				{
					tblField->type = value;
					std_field->dataType = value;
				}
				if (colName == "dflt_value")
				{
					tblField->defaultValue = value;
				}
				if (colName == "notnull")
				{
					//tblField->notnull = std::stoi(value);
					tblField->notnull = std::atoi(value.c_str());
				}
				if (colName == "pk")
				{
					//tblField->isPrimaryKey = std::stoi(value) == 1 ? true : false;
					tblField->isPrimaryKey = std::atoi(value.c_str()) == 1 ? true : false;
				}
			}
			tableFields.push_back(tblField);
		}
	}

	return false;
}

//Get record
bool SQLiteReader::readData(Table)
{
	return false;
}