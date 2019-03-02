#include "RecordProducer.h"

RecordProducer::RecordProducer(BaseDbReader* reader, BaseDbWriter* writer, StatementQueue* queue)
{
	this->m_reader = reader;
	this->m_writer = writer;
	this->m_queue = queue;
}
RecordProducer::~RecordProducer()
{

}

void RecordProducer::startGetRecord(Table* table)
{
	// loop get record tu table cua input db
	QueryModel *query = new QueryModel();
	query->table = table;
	std::vector<Record*> dataList;
	int count = 0;
	do
	{
		m_reader->readData(*query, dataList);
		count = dataList.size();
		query->skip += query->count;
		RecordStatement* statement = nullptr;
		m_writer->writeData(table->name, dataList, statement);
		dataList.clear();
		m_queue->enqueue(statement);
	}
	while (count == query->count);
}