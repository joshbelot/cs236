// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#pragma once
#include "schema.h"
#include "tuple.h"
#include "predicate.h"
#include <set>
#include <string>
#include <map>

using namespace std;

class Relation
{
private:
	string name;
	Schema schems;
	set<Tuple> tups;
	Schema addSchemes(Schema &s, vector<int> &ints);
	bool addTables(Tuple &a, Tuple &b, Schema &c);
	void addTups(Tuple &a, Tuple &b, vector<int> &ints);
public:
	Relation();
	Relation(string name);
	Relation(string name, Schema schems);
	Relation(string name, set<Tuple> tups);
	Relation(string name, Schema schems, set<Tuple> tups);

	Relation select(int posComp, int posVal);
	Relation select(int posComp, string Val);

	Relation project(vector<int> &v);
	Relation finalProject(Predicate finProj);

	Relation rename(Schema &schems);

	void uni(Relation &r);

	Relation join(Relation &r);

	string printMatches();
	string schemToString();
	string tupsToString();
	string getName();
	set<Tuple> getTups();
	int getLength();
};