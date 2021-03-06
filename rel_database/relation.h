// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#pragma once
#include "tuple.h"
#include <set>

using namespace std;

class Relation
{
public:
	Relation(string name);
	Relation(string name, vector<string> schema, set<Tuple> tups);
	string name;
	vector<string> schema;
	set<Tuple> tups;
	void insert(Tuple t);
	void add_to_schema(string s);
	Relation select1(string attrib, string val);
	Relation select2(string attrib1, string attrib2);
	Relation project(vector<string> attribs);
	void rename(vector<string> attribs);
	vector<int> return_indexes(vector<string> attribs);
	int return_index(string attrib);
	void print();
};