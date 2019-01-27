#include "stdafx.h"
#include "AccessReader.h"
#include <iostream>


AccessReader::AccessReader()
{
	AfxDaoInit();
	m_msdb = new CDaoDatabase();
}


AccessReader::~AccessReader()
{
	if (m_msdb->IsOpen())
	{
		m_msdb->Close();
		m_msdb = nullptr;
	}
}

bool AccessReader::init(const char* dbPath)
{
	CString widepath = (CString)dbPath;
	m_msdb->Open(widepath);

	return true;
}


//Get all table and form of table
bool AccessReader::readStructure(DatabaseStruct* data_info)
{

	return false;
}

void AccessReader::readTableInfo(std::vector<Table*>& tableInfos)
{
	int nTableCount = m_msdb->GetTableDefCount();
	for (int i = 0; i < nTableCount; ++i)
	{
		Table* table = new Table();
		CDaoTableDefInfo tabledefinfo;
		m_msdb->GetTableDefInfo(i, tabledefinfo);          
		if (tabledefinfo.m_lAttributes == 0)
		{
			CDaoTableDef TableDef(m_msdb);
			CT2CA pszConvertedAnsiString(tabledefinfo.m_strName);			//convert CString to std::string
			std::string strStd(pszConvertedAnsiString);
			table->name = strStd;
		}


		tableInfos.push_back(table);
	}
}

void AccessReader::readFieldInfo(CDaoTableDef &TableDef, std::vector<Field*>& fields)
{
	size_t nFieldCount = TableDef.GetFieldCount();
	for (size_t i1 = 0; i1 < nFieldCount; ++i1)
	{
		Field* field = new Field();
		CDaoFieldInfo fieldinfo;
		TableDef.GetFieldInfo(i1, fieldinfo, AFX_DAO_ALL_INFO);
		CT2CA pszConvertedAnsiString(fieldinfo.m_strName);			//convert CString to std::string
		std::string strStd(pszConvertedAnsiString);
		field->name = strStd;
		//field->dataType = fieldinfo.m_nType;						//call convert data Type func 

		
	}
}

void AccessReader::readForeignKeyInfo(const std::string& tableName, std::vector<ForeignKey*>& foreignKeys)
{

}

void AccessReader::readIndexInfo(std::vector<Index*>& indexs)
{

}

void AccessReader::readProcedureInfo(std::vector<Procedure*>& procedures)
{

}

void AccessReader::readViewInfo(std::vector<View*>& views)
{

}

void AccessReader::readTriggerInfo(std::vector<Trigger*>& triggers)
{

}

bool AccessReader::convertType(const std::string &type, CommonDataType &out)
{

	return false;
}

//Get record information 
bool AccessReader::readData(const QueryModel& query, std::vector<Record*>& dataList)
{
	return false;
}