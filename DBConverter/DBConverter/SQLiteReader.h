#pragma once
#include "BaseDbReader.h"
#include "SQLiteDatabase.h"
#include <iostream>
class SQLiteReader : public BaseDbReader 
{
public:
	SQLiteReader();
	~SQLiteReader();

	virtual bool readStructure(DatabaseStruct*);
	virtual bool readData(Table);

	bool init(const char* dbPath);

private:
	void readTableInfo(std::vector<Table*>& tableInfos);
	bool convertType(const std::string &type, CommonDataType &out);

private:
	SQLiteDatabase* m_db;
};

