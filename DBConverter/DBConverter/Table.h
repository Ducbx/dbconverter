#pragma once
#include "Field.h"
#include "Record.h"
#include <vector>

struct Table
{
	std::string name;
	std::vector<Field> fields;
	std::vector<Record> records;
};