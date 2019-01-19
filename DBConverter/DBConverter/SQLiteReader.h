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
	void readIndexInfo(std::vector<Index*>& indexs);
	void readProcedureInfo(std::vector<Procedure*>& procedures);
	void readViewInfo(std::vector<View*>& views);
	void readTriggerInfo(std::vector<Trigger*>& triggers);
	bool convertType(const std::string &type, CommonDataType &out);

private:
	SQLiteDatabase* m_db;
};

