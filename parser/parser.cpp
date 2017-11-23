#include "parser.h"
#include <vector>

using namespace std;

Parser::Parser(vector<Token> tokens)
{
	this->tokens = tokens;
	iter = 0;
}

void Parser::test(Token tok1, type tok2)
{
	if(tok1.get_type() == tok2)
	{
		iter++;
		return;
	}
	else
	{
		cout << "Failure!\n" << tok1.toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Parser::idList(Predicate &preds)
{
	//COMMA ID idList | lambda
	if(tokens[iter].get_type() != RIGHT_PAREN)
	{
		test(tokens[iter], COMMA);
		test(tokens[iter], ID);
		Parameter param = Parameter(tokens[iter-1]);
		preds.add_to_params(param);
		idList(preds);
	}
}

void Parser::scheme()
{
	//ID LEFT_PAREN ID idList RIGHT_PAREN
	test(tokens[iter], ID);
	Predicate preds = Predicate(tokens[iter-1].get_value());
	test(tokens[iter], LEFT_PAREN);
	test(tokens[iter], ID);
	Parameter param = Parameter(tokens[iter-1]);
	preds.add_to_params(param);
	idList(preds);
	test(tokens[iter], RIGHT_PAREN);
}

void Parser::schemeList()
{
	//scheme schemeList | lamda
	if(tokens[iter].get_type() != FACTS)
	{
		scheme();
		schemeList();
	}
}

void Parser::stringList(Predicate &preds)
{
	//COMMA STRING stringList | lambda
	if(tokens[iter].get_type() != RIGHT_PAREN)
	{
		test(tokens[iter], COMMA);
		test(tokens[iter], STRING);
		Parameter param = Parameter(tokens[iter-1]);
		preds.add_to_params(param);
		stringList(preds);
	}
}

void Parser::fact()
{
	// ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	test(tokens[iter], ID);
	Predicate preds = Predicate(tokens[iter-1].get_value());
	test(tokens[iter], LEFT_PAREN);
	test(tokens[iter], STRING);
	Parameter param = Parameter(tokens[iter-1]);
	preds.add_to_params(param);
	stringList(preds);
	test(tokens[iter], RIGHT_PAREN);
	test(tokens[iter], PERIOD);
}

void Parser::factList()
{
	if(tokens[iter].get_type() != RULES)
	{
		fact();
		factList();
	}
}

void Parser::datalog_parse()
{
	test(tokens[iter],SCHEMES);
	test(tokens[iter],COLON);
	scheme();
	schemeList();
	test(tokens[iter],FACTS);
	test(tokens[iter],COLON);
	factList();
	test(tokens[iter],RULES);
	test(tokens[iter],COLON);
	//ruleList();
	test(tokens[iter],QUERIES);
	test(tokens[iter],COLON);
	//query();
	//queryList();
	test(tokens[iter],E_O_F);
	cout << "Success!\n";
}