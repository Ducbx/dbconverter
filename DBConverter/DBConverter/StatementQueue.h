#pragma once
#include<queue>
#include"RecordStatement.h"
#include "semaphore.h"

class StatementQueue
{
public:
	StatementQueue(int capacity);
	~StatementQueue();
	void enqueue(const RecordStatement &statement);
	void dequeue(RecordStatement &statement);
	bool isEmpty() const { return m_queue.empty(); }
	bool isFull() const { return m_capacity == m_queue.size(); }
private:
	int m_capacity;
	std::queue<RecordStatement> m_queue;
	semaphore m_semaphoreWrite;
	semaphore m_semaphoreRead;
};
