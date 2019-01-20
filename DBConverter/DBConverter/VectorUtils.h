#pragma once
#include<iostream>

class VectorUtils
{
public:
	template<typename T>
	inline static void clearPointerVector(std::vector<T> vector)
	{
		for (std::vector<T>::iterator it = vector.begin(); it != vector.end(); ++it)
		{
			delete (*it);
		}
		vector.clear();
	}
};