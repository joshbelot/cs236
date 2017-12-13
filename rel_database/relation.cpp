// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
#include "relation.h"

Relation::Relation(string name, vector<string> schema)
{
	this->name = name;
	this->schema = schema;
}

/*
void Relation::add_tuple(vector<Pair> tups)
{

}
*/