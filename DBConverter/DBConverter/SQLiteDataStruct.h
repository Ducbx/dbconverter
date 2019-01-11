#pragma once
#include<iostream>
#include<vector>

struct SQLiteDataStruct
{
	std::vector<std::string> fields;
	std::vector<std::vector<std::string>> records;
	
	std::string toString()
	{
		std::string result = "Fields = (";
		int i = 0;
		for (i = 0; i < fields.size()-1; i++)
		{
			result += fields.at(i);
			result += ", ";
		}
		if (fields.size() - 1 == i)
		{
			result += fields.at(i);
		}
		result += "); Record = (";

		int j = 0;
		int k = 0;
		for (int j = 0; j < records.size(); j++)
		{
			std::vector<std::string>& record = records[j];
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