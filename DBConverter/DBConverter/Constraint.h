#pragma once
#include <iostream>
#include <vector>

enum class ConstraintType : int
{
	NOT_NULL, 				// - Ensures that a column cannot have a NULL value
	UNIQUE,					// - Ensures that all values in a column are different
	PRIMARY_KEY,			// - A combination of a NOT NULL and UNIQUE.Uniquely identifies each row in a table
	FOREIGN_KEY,			// - Uniquely identifies a row / record in another table
	CHECK,					// - Ensures that all values in a column satisfies a specific condition
	DEFAULT,				// - Sets a default value for a column when no value is specified
	INDEX					// - Used to create and retrieve data from the database very quickly
};

struct Constraint
{
	std::string name;
	std::string tableName;
	std::string fieldName;
	ConstraintType constraintType;
};

struct NotNullConstraint : public Constraint
{
	NotNullConstraint()
	{
		constraintType = ConstraintType::NOT_NULL;
	}
};

struct UniqueConstraint : public Constraint
{
	UniqueConstraint()
	{
		constraintType = ConstraintType::UNIQUE;
	}
};

struct PrimaryKeyConstraint : public Constraint
{
	PrimaryKeyConstraint()
	{
		constraintType = ConstraintType::PRIMARY_KEY;
	}
};

struct ForeignKeyConstraint : public Constraint
{
	ForeignKeyConstraint()
	{
		constraintType = ConstraintType::FOREIGN_KEY;
	}
	std::string refTableName;
	std::string refColumn;
	std::string action;			//ON DELETE and ON UPDATE Actions
};

struct CheckConstraint : public Constraint
{
	CheckConstraint()
	{
		constraintType = ConstraintType::CHECK;
	}
};

struct DefaultConstraint : public Constraint
{
	DefaultConstraint()
	{
		constraintType = ConstraintType::DEFAULT;
	}
	void* defaultValue;
};

struct IndexConstraint : public Constraint
{
	IndexConstraint()
	{
		constraintType = ConstraintType::INDEX;
	}
};