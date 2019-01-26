#include "stdafx.h"
#include "SQLiteReader.h"
#include "SQLiteDatabase.h"
#include "StringUtilities.h"

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
		if (tableNames->data[i][0] == "sqlite_sequence")
		{
			continue;
		}
		Table* table = new Table();
		table->name = tableNames->data[i][0];

		//Get fieldnames, fieldtypes, primary key... in each table
		readFieldInfo(table->name, table->fields);
		
		//Get foriegn key for each table
		readForeignKeyInfo(table->name, table->foreignKeys);

		tableInfos.push_back(table);
	}

	delete tableNames;
}

void SQLiteReader::readFieldInfo(const std::string& tableName, std::vector<Field*>& fields)
{
	SQLiteDataStruct* sqliteFields = new SQLiteDataStruct();
	std::string str = "PRAGMA table_info('" + tableName + "');";

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
				field->isPrimaryKey = std::atoi(value.c_str()) == 1 ? true : false;
			}
		}
		fields.push_back(field);
	}

	delete sqliteFields;
}

void SQLiteReader::readForeignKeyInfo(const std::string& tableName, std::vector<ForeignKey*>& foreignKeys)
{
	SQLiteDataStruct* sqliteForiegnKeys = new SQLiteDataStruct();
	std::string str1 = "PRAGMA foreign_key_list('" + tableName + "');";
	const char *cstr1 = str1.c_str();
	m_db->executeQuery(cstr1, sqliteForiegnKeys);

	for (size_t row = 0; row < sqliteForiegnKeys->data.size(); row++)
	{
		ForeignKey *foreignKey = new ForeignKey();
		for (size_t col = 0; col < sqliteForiegnKeys->data[row].size(); col++)
		{
			std::string foreignAttribute = sqliteForiegnKeys->columns[col];
			std::string foreignValue = sqliteForiegnKeys->data[row][col];
			if (foreignAttribute == "table")
			{
				foreignKey->refTableName = foreignValue;
			}
			if (foreignAttribute == "from")
			{
				foreignKey->refFieldName = foreignValue;
			}
			if (foreignAttribute == "to")
			{
				foreignKey->fieldName = foreignValue;
			}
			if (foreignAttribute == "on_update")
			{
				foreignKey->onUpdateAction = foreignValue;
			}
			if (foreignAttribute == "on_delete")
			{
				foreignKey->onDeleteAction = foreignValue;
			}
		}
		foreignKeys.push_back(foreignKey);
	}

	delete sqliteForiegnKeys;
}

void SQLiteReader::readIndexInfo(std::vector<Index*>& indexs)
{

	SQLiteDataStruct *sqliteIndexs = new SQLiteDataStruct();
	m_db->executeQuery("select * from sqlite_master where type = 'index';", sqliteIndexs);

	for (size_t row = 0; row < sqliteIndexs->data.size(); row++)
	{
		Index *index = new Index();
		for (size_t col = 0; col < sqliteIndexs->data[row].size(); col++)
		{
			std::string indexAttribute = sqliteIndexs->columns[col];
			std::string indexValue = sqliteIndexs->data[row][col];
			if (indexAttribute == "name")
			{
				index->name = indexValue;
			}
			if (indexAttribute == "tbl_name")
			{
				index->tableName = indexValue;
			}
		}
		indexs.push_back(index);
	}

	//get fields for each index
	for (size_t ind = 0; ind < indexs.size(); ind++)
	{
		SQLiteDataStruct* sqliteIndexFields = new SQLiteDataStruct();
		std::string sqlite = "PRAGMA index_info('" + indexs[ind]->name + "');";
		const char *cstr3 = sqlite.c_str();
		m_db->executeQuery(cstr3, sqliteIndexFields);

		for (size_t row = 0; row < sqliteIndexFields->data.size(); row++)
		{
			for (size_t col = 0; col < sqliteIndexFields->data[row].size(); col++)
			{
				std::string colName = sqliteIndexFields->columns[col];
				std::string value = sqliteIndexFields->data[row][col];
				if (colName == "name")
				{
					indexs[ind]->fieldNames.push_back(value);
				}
			}
		}
		delete sqliteIndexFields;
	}

	//check unique
	SQLiteDataStruct *sqliteIndexUnique = new SQLiteDataStruct();
	m_db->executeQuery("SELECT name FROM sqlite_master WHERE type = 'index' AND sql like '%UNIQUE%';", sqliteIndexUnique);
	for (size_t ind = 0; ind < indexs.size(); ind++)
	{
		for (size_t row = 0; row < sqliteIndexUnique->data.size(); row++)
		{
			if (sqliteIndexUnique->data[row][0] == indexs[ind]->name)
			{
				indexs[ind]->isUnique = true;
			}
		}
	}

	delete sqliteIndexs;
	delete sqliteIndexUnique;

}

void SQLiteReader::readProcedureInfo(std::vector<Procedure*>& procedures)
{

}
void SQLiteReader::readViewInfo(std::vector<View*>& views)
{
	SQLiteDataStruct *sqliteViews = new SQLiteDataStruct();
	m_db->executeQuery("select sql from sqlite_master where type = 'view';", sqliteViews);
	
	//Handle string to model format


	delete sqliteViews;
}
void SQLiteReader::readTriggerInfo(std::vector<Trigger*>& triggers)
{
	SQLiteDataStruct *sqliteTriggers = new SQLiteDataStruct();
	m_db->executeQuery("select sql from sqlite_master where type = 'view';", sqliteTriggers);

	//Handle string to model format

	delete sqliteTriggers;
}

bool SQLiteReader::convertType(const std::string &type, CommonDataType &out)
{
	if (StringUtilities::compareStringInsensitive(type, "Integer"))
	{
		out = CommonDataType::Integer;
	}
	else if (StringUtilities::compareStringInsensitive(type, "real"))
	{
		out = CommonDataType::Double;
	}
	else if (StringUtilities::compareStringInsensitive(type, "text") || StringUtilities::compareStringInsensitive(type, "blob"))
	{
		out = CommonDataType::String;
	}
	else if (StringUtilities::compareStringInsensitive(type, "boolean"))
	{
		out = CommonDataType::Boolean;
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
	readIndexInfo(data_info->indexs);
	return false;
}

//Get record
bool SQLiteReader::readData(Table)
{
	return false;
}