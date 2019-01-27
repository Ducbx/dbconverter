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
	virtual bool readData(const QueryModel& query, std::vector<Record*>& dataList);

	bool init(const char* dbPath);

private:
	void readTableInfo(std::vector<Table*>& tableInfos);
	void readFieldInfo(const std::string& tableName, std::vector<Field*>& fields);
	void readForeignKeyInfo(const std::string& tableName, std::vector<ForeignKey*>& foreignKeys);
	void readIndexInfo(std::vector<Index*>& indexs);
	void readProcedureInfo(std::vector<Procedure*>& procedures);
	void readViewInfo(std::vector<View*>& views);
	void readTriggerInfo(std::vector<Trigger*>& triggers);
	bool convertType(const std::string &type, CommonDataType &out);

private:
	SQLiteDatabase* m_db;
};

