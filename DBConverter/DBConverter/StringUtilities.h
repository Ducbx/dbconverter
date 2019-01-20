#pragma once
#include<iostream>
#include <cctype>

class StringUtilities
{
public:
	inline static bool compareStringInsensitive(const std::string& str1, const std::string& str2)
	{
		return ((str1.size() == str2.size()) &&
			std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar));

#if 0
		if (str1.size() != str2.size())
		{
			return false;
		}

		std::string::const_iterator it2 = str2.begin();
		for (std::string::const_iterator it = str1.begin(); it != str1.end(); ++it, ++it2)
		{
			if (!compareChar(*it, *it2))
			{
				return false;
			}
		}

		return true;
#endif
	}

	static bool compareChar(const char & c1, const char & c2)
	{
		if (c1 == c2)
			return true;
		else if (std::toupper(c1) == std::toupper(c2))
			return true;
		return false;
	}
};