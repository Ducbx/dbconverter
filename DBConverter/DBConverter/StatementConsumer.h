#pragma once
#include "BaseStatementExecutor.h"
#include "StatementQueue.h"

class StatementConsumer
{
public:
	StatementConsumer(BaseStatementExecutor *statementExecutor, StatementQueue* queue);
	~StatementConsumer();

	void startConsum();
	void stop();

private:
	BaseStatementExecutor* m_statementExecutor;
	StatementQueue* m_queue;
	bool m_isStop;
};