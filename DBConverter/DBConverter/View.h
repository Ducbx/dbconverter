#pragma once
#include <iostream>
#include <vector>

struct View
{
	std::string name;
	std::vector<std::string> fields;
	std::string tableName;
	std::string condition;
};