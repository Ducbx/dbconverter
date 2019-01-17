#include "stdafx.h"
#include "AccessReader.h"
#include <afxdao.h>


AccessReader::AccessReader()
{
}


AccessReader::~AccessReader()
{
}

//Get all table and form of table
bool AccessReader::readStructure(const char* path, DatabaseStruct* data_info)
{
#if 0
	//open access DB
	CDaoDatabase* accessDB = new CDaoDatabase();
	accessDB->Open((CString)path);

	//Get count table
	int nTableCount = accessDB->GetTableDefCount();
	//get infor table from mdb
	for (int i = 0; i < nTableCount; ++i)
	{
		CDaoTableDefInfo tabledefinfo;
		//get table from mdb to tabledefinfor(table by table for each i) 
		accessDB->GetTableDefInfo(i, tabledefinfo);
		//table name: tabledefinfo.m_strName
		//CDaoFieldInfo fieldinfo;

		//TableDef.GetFieldInfo(i1, fieldinfo, AFX_DAO_ALL_INFO);
		//db.GetRelationInfo(i1,relationinfo,AFX_DAO_ALL_INFO); --> trigger
		
		//CDaoIndexInfo indexinfo;
		//TableDef.GetIndexInfo(i1, indexinfo, AFX_DAO_ALL_INFO);
	}
#endif
	return false;
}


//Get record information 
bool AccessReader::readData(Table)
{
	return false;
}