#pragma once

#include <iostream>
struct QueryModel
{
	std::string tableName; // query from this table name
	
	// fir paging
	int limit; // number of record want to take
	int skip;  // number of record to skip
	int lastDataId; // for paging uisng id, because id field is automatically indexed by database
};