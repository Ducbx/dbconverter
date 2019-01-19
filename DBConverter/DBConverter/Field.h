#pragma once
#include<iostream>
#include "CommonDefs.h"

struct Field
{
	std::string name;
	CommonDataType dataType;
	std::string defaultValue;
	int dataSize; // -1 means not set
	std::string checkCondition;	// check constraint
	bool isUnique;
	bool isNotNull;
	bool isAutoIncrement;

	Field()
		: name(""),
		defaultValue(""),
		dataSize(-1),
		checkCondition(""),
		isUnique(false),
		isNotNull(false),
		isAutoIncrement(false)
	{
	}
};