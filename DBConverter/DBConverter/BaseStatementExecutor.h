#pragma once
#include "StructureStatement.h"
#include "RecordStatement.h"

class BaseStatementExecutor
{
public:
	virtual ~BaseStatementExecutor(){}
	virtual inline bool init(char* outputPath)
	{
		m_outputPath = outputPath;
		return true;
	}

	virtual bool executeDbStructureStatement(const StructureStatement* outputStatement)=0;
	virtual bool executeRecordStatement(const RecordStatement* recordStatement) = 0;

protected:
	std::string m_outputPath;
};