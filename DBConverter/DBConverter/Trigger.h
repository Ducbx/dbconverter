#pragma once
#include <iostream>
#include <vector>

struct Trigger
{
	std::string name;
	std::vector<std::string> statements;
	std::string tableName;
	std::string eventName;
	std::string executeTime;
};