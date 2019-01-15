#pragma once
#include<iostream>
#include<vector>

struct SQLiteDataStruct
{
	std::vector<std::string> columns;
	std::vector<std::vector<std::string>> data;
	
	void reset()
	{
		data.clear();
		columns.clear();
	}

	std::string toString()
	{
		std::string result = "Fields = (";
		size_t i = 0;
		for (i = 0; i < columns.size() - 1; i++)
		{
			result += columns.at(i);
			result += ", ";
		}
		if (columns.size() - 1 == i)
		{
			result += columns.at(i);
		}
		result += "); Record = (";

		size_t j = 0;
		size_t k = 0;
		for (j = 0; j < data.size(); j++)
		{
			std::vector<std::string>& record = data[j];
			std::string temp = "(";
			for (k = 0; k < record.size() - 1; k++)
			{
				temp += record.at(k);
				temp += ", ";
			}
			if (record.size() - 1 == k)
			{
				temp += record.at(k);
			}
			temp += ")";
			//only append comma "," if this is not the last record of record list
			if (j != record.size() - 1)
			{
				temp += ", ";
			}
			result += temp;
		}
		result += ")";
	}
};