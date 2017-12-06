// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#include "relation.h"

using namespace std;

Relation::Relation(string name)
{
	this->name = name;
}

Relation Relation::select_si(string attrib, string value)
{

}

Relation Relation::select_ss(string attrib1, string attrib2)
{

}

Relation Relation::project(vector<string> attribs)
{

}

void Relation::rename(vector<string> attribs)
{
	
}