#pragma once
#include "BaseDbReader.h"
#include "BaseDbWriter.h"
#include "StatementQueue.h"
#include "Table.h"
class RecordProducer
{
public:
	RecordProducer(BaseDbReader* reader, BaseDbWriter* writer, StatementQueue* queue);
	~RecordProducer();

	void startGetRecord(Table* table);

private:
	BaseDbReader* m_reader;
	BaseDbWriter* m_writer;
	StatementQueue* m_queue;
};