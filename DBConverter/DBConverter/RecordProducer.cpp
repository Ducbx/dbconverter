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
	//m_reader->readData()

	//std::vector<Record*> dataList;
	//m_reader->readData(,dataList);
	
	//RecordStatement* statement = nullptr;
	//m_writer->writeData(dataList, statement);

	//m_queue->enqueue(statement);
}