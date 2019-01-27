#ifndef Base_Db_Reader_h
#define Base_Db_Reader_h
#include "DatabaseStruct.h"
#include "QueryModel.h"

class  BaseDbReader
{
public:
	virtual ~BaseDbReader(){}
	virtual bool readStructure(DatabaseStruct*) = 0;
	virtual bool readData(const QueryModel& query, std::vector<Record*>& dataList) = 0;
};
#endif