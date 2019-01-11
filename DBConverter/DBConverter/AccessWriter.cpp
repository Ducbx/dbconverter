#include "stdafx.h"
#include "AccessWriter.h"


AccessWriter::AccessWriter()
{
}


AccessWriter::~AccessWriter()
{
}


bool AccessWriter::writeStructure(DatabaseStruct &)
{
	return false;
}

bool AccessWriter::writeData(Table)
{
	return false;
}