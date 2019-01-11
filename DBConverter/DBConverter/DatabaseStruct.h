#pragma once
#include "Table.h"
#include "Constraint.h"
#include "Procedure.h"
#include "Trigger.h"
#include "Index.h"
#include "View.h"

struct DatabaseStruct
{
	std::vector<Table*> tables;
	std::vector<View*> views;
	std::vector<Trigger*> triggers;
	std::vector<Procedure*> procedures;
	std::vector<Index*> indexs;
	std::vector<Constraint*> constraints;
};
