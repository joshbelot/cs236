#pragma once
#include <vector>
#include "token.h"

using namespace std;

class Parser
{
private:
	vector<Token> tokens;
	int iter;
public:
	Parser(vector<Token> tokens);
	void test(Token tok1, type tok2);
	void datalog_parse();
};