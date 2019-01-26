#pragma once
#include "BaseOutputWriter.h"

class AccessOutputWriter: public BaseOutputWriter
{
public:
	virtual ~AccessOutputWriter(){}
	virtual bool generateOutput(char* outputPath, const OutputStatement* &outputStatement);
};