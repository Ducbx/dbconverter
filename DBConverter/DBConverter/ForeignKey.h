#pragma once
#include<iostream>

struct ForeignKey
{
	std::string name;
	std::string fieldName;
	std::string refTableName;
	std::string refFieldName;
	std::string onUpdateAction;
	std::string onDeleteAction;

	ForeignKey()
		: name(""),
		fieldName(""),
		refTableName(""),
		refFieldName(""),
		onUpdateAction(""),
		onDeleteAction("")
	{
	}
};



