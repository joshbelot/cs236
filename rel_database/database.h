#pragma once
#include "Rule.h"
#include "Relation.h"
#include "Pair.h"

using namespace std;

class Database
{
private:
	vector<Predicate> schems;
	vector<Predicate> facts;
	vector<Rule> rules;
	vector<Predicate> queries;
	set<string> domain;
	vector<Relation> relations;
public:
	Database();
	void add_to_schema(Predicate p);
	void add_to_facts(Predicate p);
	void add_to_queries(Predicate p);
	void add_to_domain(string s);
	Relation get(string n);
	Relation solve_query(Predicate p);
	void solve_queries();
	void print();
};