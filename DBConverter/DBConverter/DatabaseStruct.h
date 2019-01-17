#pragma once
#include "Table.h"
#include "Procedure.h"
#include "Trigger.h"
#include "Index.h"
#include "View.h"
#include "VectorUtils.h"

struct DatabaseStruct
{
	std::vector<Table*> tables;
	std::vector<View*> views;
	std::vector<Trigger*> triggers;
	std::vector<Procedure*> procedures;
	std::vector<Index*> indexs;

	~DatabaseStruct()
	{
		// cleanup tables
		VectorUtils::clearPointerVector<Table*>(tables);
	}
};
