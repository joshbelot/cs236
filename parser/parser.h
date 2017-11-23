#pragma once
#include <vector>
#include "token.h"
#include "predicate.h"

using namespace std;

class Parser
{
private:
	vector<Token> tokens;
	int iter;
public:
	Parser(vector<Token> tokens);
	void test(Token tok1, type tok2);
	void idList(Predicate &preds);
	void scheme();
	void schemeList();
	void stringList(Predicate &preds);
	void fact();
	void factList();
	void datalog_parse();
};