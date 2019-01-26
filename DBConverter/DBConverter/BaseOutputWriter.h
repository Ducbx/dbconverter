#pragma once
#include "OutputStatement.h"

class BaseOutputWriter
{
public:
	virtual ~BaseOutputWriter(){}
	virtual bool generateOutput(char* outputPath, const OutputStatement* &outputStatement);
};