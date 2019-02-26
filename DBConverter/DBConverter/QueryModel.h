#pragma once

#include "Table.h"
#include <iostream>
struct QueryModel
{
	Table* table; // query from this table
	
	// for paging
	int count; // number of record want to take
	int skip;  // number of record to skip
	int lastDataId; // for paging uisng id, because id field is automatically indexed by database
};