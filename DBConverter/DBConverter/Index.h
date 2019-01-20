#pragma once
#include <iostream>
#include <vector>

struct Index
{
	std::string name;
	std::string tableName;
	std::vector<std::string> fieldNames;
	bool isUnique;

	Index()
		:name(""),
		tableName(""),
		isUnique(false)
	{
	}
};