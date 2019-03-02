#include "StatementConsumer.h"

StatementConsumer::StatementConsumer(BaseStatementExecutor *statementExecutor, StatementQueue* queue)
{
	this->m_queue = queue;
	this->m_statementExecutor = statementExecutor;
	m_isStop = false;
}

void StatementConsumer::stop()
{
	m_isStop = true;
}

void StatementConsumer::startConsum()
{
	while (!m_isStop)
	{
		RecordStatement *statement = nullptr;
		m_queue->dequeue(statement);
		if (statement)
		{
			m_statementExecutor->executeRecordStatement(statement);
			delete statement;
		}
	}
}