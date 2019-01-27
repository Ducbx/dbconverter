#include "AccessStatementExecutor.h"

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

AccessStatementExecutor::~AccessStatementExecutor()
{
	if (m_db)
	{
		if (m_db->IsOpen())
		{
			m_db->Close();
		}

		delete m_db;
		m_db = NULL;
	}
}
bool AccessStatementExecutor::init(char* outputPath)
{
	BaseStatementExecutor::init(outputPath);
	
	// Remove old file if exist
	if (fileExists(m_outputPath)) {
		fileRemove(m_outputPath);
	}

	// Open file
	AfxDaoInit();
	m_db = new CDaoDatabase();
	CString lpszFile = m_outputPath.c_str();
	m_db->Create(lpszFile, dbLangGeneral, 0);

	if (!m_db->IsOpen())
	{
		printf("Fail to open database %s", outputPath);
		return false;
	}
	return true;
}

bool AccessStatementExecutor::fileExists(const std::string &name)
{
	std::string path = name;
	path += ".mdb";
	if (FILE *file = fopen(path.c_str(), "r"))
	{
		fclose(file);
		return true;
	}

	return false;
}

void AccessStatementExecutor::fileRemove(const std::string &name)
{
	std::string path = name;
	path += ".mdb";
	remove(path.c_str());
}

bool AccessStatementExecutor::executeDbStructureStatement(const StructureStatement* outputStatement)
{
	for (size_t table = 0; table < outputStatement->tableStatement.size(); table++)
	{
		CString sqlTableCreate = outputStatement->tableStatement[table].c_str();
		try
		{
			m_db->Execute(sqlTableCreate);
		}
		catch (CDaoException* ex)
		{
			printf("%s", ex->m_pErrorInfo->m_strDescription);
		}
	}
	return true;
}

bool AccessStatementExecutor::executeRecordStatement(const RecordStatement* recordStatement)
{
	return false;
}