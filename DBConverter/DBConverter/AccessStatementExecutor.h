#pragma once
#include "BaseStatementExecutor.h"
#include <afxdao.h>

#pragma warning(disable : 4995)

class AccessStatementExecutor: public BaseStatementExecutor
{
public:
	virtual ~AccessStatementExecutor();

	virtual bool init(char* outputPath);
	virtual bool executeDbStructureStatement(const StructureStatement* outputStatement);
	virtual bool executeRecordStatement(const RecordStatement* recordStatement);

private:
	bool fileExists(const std::string &name);
	void fileRemove(const std::string &name);

private:
	CDaoDatabase *m_db;
};