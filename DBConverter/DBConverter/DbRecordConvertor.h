#pragma once
#include "StatementConsumer.h"
#include "RecordProducer.h"
#include "StatementQueue.h"

class DbRecordConvertor
{
public:
	DbRecordConvertor(RecordProducer* producer, StatementConsumer* consumer, StatementQueue* queue);
	~DbRecordConvertor();
	bool start(std::vector<Table*> tblList);

private:
	void startProducer(std::vector<Table*> tblList);
	void startConsumer();

private:
	StatementConsumer* m_consumer;
	RecordProducer* m_producer;
	StatementQueue* m_queue;
};