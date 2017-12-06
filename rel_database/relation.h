// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#pragma once
#include <set>

using namespace std;

class Relation
{
public:
	Relation(string name);
	Relation select_si(string attrib, string value);
	Relation select_ss(string attrib1, string attrib2);
	Relation project(vector<string> attribs);
	void rename(vector<string> attribs);
};