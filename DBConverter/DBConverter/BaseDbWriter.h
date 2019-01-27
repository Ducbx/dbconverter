#ifndef Base_Db_Writer_h
#define Base_Db_Writer_h
#include "DatabaseStruct.h"
#include "StructureStatement.h"
#include "RecordStatement.h"

class  BaseDbWriter
{
public:
	virtual bool writeStructure(DatabaseStruct* &databaseStruct, StructureStatement* &outputStatement) = 0;
	virtual bool writeData(std::vector<Record> records, RecordStatement* recordStatement) = 0;
};


#endif