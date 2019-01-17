#include "stdafx.h"
#include "SQLiteReader.h"
#include "SQLiteDatabase.h"

SQLiteReader::SQLiteReader()
{
	m_db = new SQLiteDatabase();
}

SQLiteReader::~SQLiteReader()
{
	if (m_db)
	{
		delete m_db;
		m_db = nullptr;
	}
}


bool SQLiteReader::init(const char* dbPath)
{
	if (!m_db || !m_db->openDb(dbPath))
	{
		std::cout << "False to open SQLite DB";
		return false;
	}

	return true;
}

void SQLiteReader::readTableInfo(std::vector<Table*>& tableInfos)
{
	SQLiteDataStruct *tableNames = new SQLiteDataStruct();
	m_db->executeQuery("SELECT name FROM sqlite_master WHERE type='table';", tableNames);

	for (size_t i = 0; i < tableNames->data.size(); i++)
	{
		Table* table = new Table();
		table->name = tableNames->data[i][0];

		SQLiteDataStruct* sqliteFields = new SQLiteDataStruct();
		std::string str = "PRAGMA table_info('" + tableNames->data[i][0] + "');";

		const char *cstr = str.c_str();
		m_db->executeQuery(cstr, sqliteFields);

		for (size_t row = 0; row < sqliteFields->data.size(); row++)
		{
			Field* field = new Field();
			for (size_t col = 0; col < sqliteFields->data[row].size(); col++)
			{
				std::string& colName = sqliteFields->columns[col];
				std::string& value = sqliteFields->data[row][col];

				if (colName == "name")
				{
					field->name = value;
				}
				if (colName == "type")
				{
					convertType(value, field->dataType);
				}
				if (colName == "notnull")
				{
					field->isNotNull = std::atoi(value.c_str()) == 1 ? true : false;
				}
				if (colName == "dflt_value")
				{
					field->defaultValue = value;
				}
				if (colName == "pk")
				{
					bool isPrimaryKey = std::atoi(value.c_str()) == 1 ? true : false;
					if (isPrimaryKey)
					{
						table->primaryKey.fieldNames.push_back(field->name);
					}
				}
			}
			table->fields.push_back(field);
		}

		tableInfos.push_back(table);
	}
}

bool SQLiteReader::convertType(const std::string &type, CommonDataType &out)
{
	if (type == "integer")
	{
		out = CommonDataType::Integer;
	}
	else if (type == "real")
	{
		out = CommonDataType::Double;
	}
	else if (type == "text" || type == "blob")
	{
		out = CommonDataType::String;
	}
	else
	{		
		// Default set text
		out = CommonDataType::String;
		printf("Unhandle sqlite data type: %s", type);
	}

	return true;
}



bool SQLiteReader::readStructure(DatabaseStruct* data_info)
{
	readTableInfo(data_info->tables);
	return false;
}

//Get record
bool SQLiteReader::readData(Table)
{
	return false;
}