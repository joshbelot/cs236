// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#pragma once
#include "tuple.h"
#include "pair.h"
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
	vector<Pair> shared(const vector<string>& schema1, const vector<string>& schema2);
	vector<string> make_new_schema(const vector<string>& schema1, const vector<string>& schema2);
	bool compatible(Tuple t1, Tuple t2, const vector<Pair>& pairs);
	Tuple merge_tuples(Tuple t1, Tuple t2, const vector<Pair>& pairs, const vector<string>& new_schema);
	Relation join(const Relation& r1, const Relation& r2);
	bool is_found(const vector<string>& v, string s);
	void print();
};