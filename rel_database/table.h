// This class needs to get information from the datalog parser and create
// a table, with a table name, vector<string> headers, and set<vector<string>> rows
// The database class pulls from here and relations to perform the queries. 
#pragma once

using namespace std;

/*
scheme = relation.
	name of relation
	attribute list = schema of relation

fact = tuple in a relation
	name identifies the relation

query = select, project, & rename
*/

class Table
{
private:
	string table_name;
	vector<string> header;
	set<vector<string>> row;
public:
	Table();
};