#include "stdafx.h"
#include "SQLiteReader.h"
#include "SQLiteDatabase.h"

SQLiteReader::SQLiteReader()
{
	//???
}


SQLiteReader::~SQLiteReader()
{
	//???
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
		//Create and save info of each table
		Table *std_table = new Table();																			
		Constraint* std_const = new Constraint();
		View* std_view = new View();
		Trigger* std_trigger = new Trigger();
		Procedure* std_procedure = new Procedure();
		Index* std_index = new Index();

		std_table->name = tableNames->data[i][1];

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
		for (size_t row = 0; row<sqliteFields->data.size(); row++)
		{
			Field* std_field = new Field();										
			SqliteTableField* tblField = new SqliteTableField();
			for (size_t col = 0; col<sqliteFields->data[row].size(); col++)
			{
				std::string& colName = sqliteFields->columns[col];
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
					//type cast dflt_value to dataType ???
					//tblField->defaultValue = value;
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
		//list down all the indexes database : sqlite> SELECT * FROM sqlite_master WHERE type = 'index';
		//refer: https://www.tutorialspoint.com/sqlite/sqlite_indexes.htm

		//list down all the triggers from sqlite_master table: sqlite> SELECT name FROM sqlite_master WHERE type = 'trigger';
		//sqlite> SELECT name FROM sqlite_master WHERE type = 'trigger' AND tbl_name = 'COMPANY';

		//SELECT name from sqlite_master WHERE type = 'view';
		//SELECT name FROM sqlite_master WHERE type = 'view' and sql LIKE "%_tablename_%";

		data_info.tables.push_back(std_table);
		data_info.constraints.push_back(std_const);
		data_info.indexs.push_back(std_index);
		data_info.procedures.push_back(std_procedure);
		data_info.triggers.push_back(std_trigger);
		data_info.views.push_back(std_view);
	}

	return false;
}

//Get record
bool SQLiteReader::readData(Table)
{
	return false;
}