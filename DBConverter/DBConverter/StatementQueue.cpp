#include "StatementQueue.h"

StatementQueue::StatementQueue(int capacity)
{
	m_capacity = capacity;
}

StatementQueue::~StatementQueue()
{
}

void StatementQueue::enqueue(const RecordStatement &statement)
{
	if (isFull())
	{
		// wait write
		m_semaphoreWrite.wait();
	}
	
	// write acquired
	m_queue.push(statement);
	// notify read
	m_semaphoreRead.notify();
}

void StatementQueue::dequeue(RecordStatement &statement)
{
	if (isEmpty())
	{
		// wait read
		m_semaphoreRead.wait();
	}
	// read acquired
	statement = m_queue.back();
	// notify write
	m_semaphoreWrite.notify();
}