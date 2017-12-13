// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#pragma once

using namespace std;

class Relation
{
private:
	string name;
	vector<string> schema;
public:
	Relation(string name);
	void add_to_schema(string schem);
	//void add_tuple(vector<Pair> tups);
};