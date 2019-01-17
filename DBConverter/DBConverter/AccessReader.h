#pragma once
#include "BaseDbReader.h"

class AccessReader : public BaseDbReader
{
public:
	AccessReader();
	~AccessReader();

	virtual bool readStructure(const char* path, DatabaseStruct* data_info);
	virtual bool readData(Table);
};

