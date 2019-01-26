#pragma once
#include "BaseDbWriter.h"
#include "DatabaseStruct.h"
#include "OutputStatement.h"

class AccessWriter : public BaseDbWriter
{
public:
	AccessWriter();
	~AccessWriter();

	virtual bool writeStructure( DatabaseStruct* &databaseStruct, OutputStatement* &outputStatement);
	virtual bool writeData(Table);
private:
	bool writeTableInfo( Table* &dataTable, std::string& tableStatement);
	bool writeIndex( Index* &dataIndex, std::string& indexStatement);
	std::string getDataType(const CommonDataType& commonDataType);
};

