#include "StatementQueue.h"

StatementQueue::StatementQueue(int capacity)
{
	m_capacity = capacity;
	m_isStop = false;
}

StatementQueue::~StatementQueue()
{
}

void StatementQueue::enqueue(RecordStatement* statement)
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

void StatementQueue::stop()
{
	m_isStop = true;
	m_semaphoreRead.notify();
}

void StatementQueue::dequeue(RecordStatement* statement)
{
	if (m_isStop)
	{
		return;
	}
	if (isEmpty())
	{
		// wait read
		m_semaphoreRead.wait();
	}
	// read acquired
	statement = m_queue.back();
	m_queue.pop();
	// notify write
	m_semaphoreWrite.notify();
}