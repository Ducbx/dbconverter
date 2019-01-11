#pragma once
#include "BaseDbReader.h"

class AccessReader : public BaseDbReader
{
public:
	AccessReader();
	~AccessReader();

	virtual bool readStructure(DatabaseStruct &);
	virtual bool readData(Table);
};

