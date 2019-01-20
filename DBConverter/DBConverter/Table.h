#pragma once
#include "Field.h"
#include "PrimaryKey.h"
#include "Record.h"
#include "ForeignKey.h"
#include <vector>

struct Table
{
	std::string name;
	std::vector<Field*> fields;
	std::vector<Record*> records;
	//PrimaryKey primaryKey;
	std::vector<ForeignKey*> foreignKeys;
};