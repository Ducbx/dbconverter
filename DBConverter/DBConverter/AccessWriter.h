#pragma once
#include "BaseDbWriter.h"

class AccessWriter : public BaseDbWriter
{
public:
	AccessWriter();
	~AccessWriter();

	virtual bool writeStructure(DatabaseStruct &);
	virtual bool writeData(Table);
};

