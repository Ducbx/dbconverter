#pragma once

#include "BaseDbReader.h"
#include <afxdao.h>

class AccessReader : public BaseDbReader
{
public:
	AccessReader();
	~AccessReader();

	virtual bool readStructure(DatabaseStruct* data_info);
	virtual bool readData(Table);

	bool init(const char* dbPath);

private:
	void readTableInfo(std::vector<Table*>& tableInfos);
	void readFieldInfo(CDaoTableDef &TableDef, std::vector<Field*>& fields);
	void readForeignKeyInfo(const std::string& tableName, std::vector<ForeignKey*>& foreignKeys);
	void readIndexInfo(std::vector<Index*>& indexs);
	void readProcedureInfo(std::vector<Procedure*>& procedures);
	void readViewInfo(std::vector<View*>& views);
	void readTriggerInfo(std::vector<Trigger*>& triggers);
	bool convertType(const std::string &type, CommonDataType &out);

private:
	CDaoDatabase* m_msdb;
};

