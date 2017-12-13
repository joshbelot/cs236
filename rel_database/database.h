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
};