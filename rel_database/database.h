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
	void add_to_schemes(Predicate p);
	void add_to_facts(Predicate p);
	void add_to_rules(Rule r);
	void add_to_queries(Predicate p);
	void add_to_domains(string s);
	void print();
	void create_relations();
	void populate_relations();
	void print_relations();
	vector<Predicate> return_schemes();
	vector<Predicate> return_facts();
	vector<Rule> return_rules();
	vector<Predicate> return_queries();
	Relation return_relation(unsigned int index);
	Relation get(string n);
	Relation& get2(string n);
	Relation solve_query(Predicate p);
	void solve_queries();
	bool is_found(const vector<Pair>& v, string s);
	int pair_index(const vector<Pair>& v, string s);
	bool is_query_all_strings(Predicate p);
	bool evaluate_rule(Rule r);
	void evaluate_rules();
};