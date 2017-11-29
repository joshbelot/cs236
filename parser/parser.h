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
	set<string> domains;
public:
	Parser(vector<Token> tokens);
	void test(Token tok1, type tok2);
	void idList(Predicate &preds, string &section);
	void scheme();
	void schemeList();
	void stringList(Predicate &preds, string &section);
	void fact();
	void factList();
	Predicate headPredicate();
	void oper(Predicate &pred);
	void expression(Predicate &pred, string &section);
	void parameter(Predicate &pred, string &section);
	void parameterList(Predicate &pred, string &section);
	void pred_to_rules(Rule &newRule);
	void predicateList(Rule &newRule);
	void rule();
	void ruleList();
	Predicate predicate(string &section);
	void query();
	void queryList();
	void datalog_parse();
	void add_to_section(Token tok, string &content);
	void printDatalog();
};