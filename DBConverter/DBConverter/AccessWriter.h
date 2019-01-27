#pragma once
#include "BaseDbWriter.h"
#include "DatabaseStruct.h"
#include "StructureStatement.h"

class AccessWriter : public BaseDbWriter
{
public:
	AccessWriter();
	~AccessWriter();

	virtual bool writeStructure( DatabaseStruct* &databaseStruct, StructureStatement* &outputStatement);
	virtual bool writeData(std::vector<Record> records, RecordStatement* recordStatement);
private:
	bool writeTableInfo( Table* &dataTable, std::string& tableStatement);
	bool writeIndex( Index* &dataIndex, std::string& indexStatement);
	std::string getDataType(const CommonDataType& commonDataType);
};

