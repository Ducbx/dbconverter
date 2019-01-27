#include "stdafx.h"
#include "AccessWriter.h"


AccessWriter::AccessWriter()
{
}


AccessWriter::~AccessWriter()
{
}


bool AccessWriter::writeStructure( DatabaseStruct* &databaseStruct, StructureStatement* &outputStatement)
{
	std::string tableState = "";
	std::string indexState = "";
	for (unsigned int table = 0; table < databaseStruct->tables.size(); table++)
	{
		writeTableInfo(databaseStruct->tables[table], tableState);
		outputStatement->tableStatement.push_back(tableState);
	}
	for (size_t index = 0; index < databaseStruct->indexs.size(); index++)
	{
		writeIndex(databaseStruct->indexs[index], indexState);
		outputStatement->indexStatement.push_back(indexState);
	}
	
	return true;
}

bool AccessWriter::writeTableInfo( Table* &dataTable, std::string& tableStatement)
{
	std::string statement = "";
	std::string fieldstate = "";
	std::string primaryKey = "";
	statement += "create table ";

	// check dataTable->name vs ACCESS keyword
	statement += dataTable->name;
	statement += " ( ";
	for (size_t field = 0; field < dataTable->fields.size(); field++)
	{
		if (fieldstate != "")
		{
			fieldstate += ",";
		}

		// check dataTable->fields[field]->name dataTable->fields[field]->name
		fieldstate += dataTable->fields[field]->name;
		fieldstate += " ";
		fieldstate += getDataType(dataTable->fields[field]->dataType);
		fieldstate += " ";
		if (dataTable->fields[field]->isNotNull)
		{
			fieldstate += " NOT NULL ";
		}
		if (dataTable->fields[field]->isPrimaryKey)
		{
			if (primaryKey != "")
			{
				primaryKey += ",";
			}
			primaryKey += dataTable->fields[field]->name;
		}
	}
	statement += fieldstate;
	statement += " , CONSTRAINT PK PRIMARY KEY (";
	statement += primaryKey;
	statement += "));";

	tableStatement = statement;
	return true;
}

bool AccessWriter::writeIndex( Index* &dataIndex, std::string& indexStatement)
{
	std::string statement = "";
	std::string fieldd = "";
	if (dataIndex->isUnique){
		statement += "Create unique index ";
	}
	else
	{
		statement += "Create index ";
	}
	statement += dataIndex->name;
	statement += " ON ";
	statement += dataIndex->tableName;
	for (size_t fi = 0; fi < dataIndex->fieldNames.size(); fi++)
	{
		if (fieldd != "")
		{
			fieldd += ",";
		}
		fieldd += dataIndex->fieldNames[fi];
	}
	statement += "(";
	statement += fieldd;
	statement += ");";

	indexStatement = statement;
	return true;
}

std::string AccessWriter::getDataType(const CommonDataType& commonDataType)
{
	std::string dataType = "";
	switch (commonDataType)
	{
	case CommonDataType::Boolean:
		dataType = "YESNO";
		break;
	case CommonDataType::Double:
		dataType = "Double";
		break;
	case CommonDataType::Integer:
		dataType = "Integer";
		break;
	case CommonDataType::String:
		dataType = "Text";
		break;
	}
	return dataType;
}

bool AccessWriter::writeData(std::vector<Record> records, RecordStatement* recordStatement)
{
	return false;
}