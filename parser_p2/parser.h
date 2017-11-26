#pragma once
#include <vector>
#include "token.h"
#include "predicate.h"
#include "Rule.h"

using namespace std;

class Parser
{
private:
	vector<Token> tokens;
	int iter;
	int numSchemes;
	int numFacts;
	int numRules;
	int numQuer;
	int numDomain;
	string schemes;
	string facts;
	string rules;
	string quers;
	string domains;
public:
	Parser(vector<Token> tokens);
	void test(Token tok1, type tok2);
	void idList(Predicate &preds);
	void scheme();
	void schemeList();
	void stringList(Predicate &preds);
	void fact();
	void factList();
	Predicate headPredicate();
	void oper(Predicate &pred);
	void expression(Predicate &pred);
	void parameter(Predicate &pred);
	void parameterList(Predicate &pred);
	void pred_to_rules(Rule &newRule);
	void predicateList(Rule &newRule);
	void rule();
	void ruleList();
	Predicate predicate();
	void query();
	void queryList();
	void datalog_parse();
	void add_to_schemes(Token tok, string &content);
	void printDatalog();
};