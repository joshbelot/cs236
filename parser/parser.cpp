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

Predicate Parser::headPredicate()
{
	//ID LEFT_PAREN ID idList RIGHT_PAREN
	test(tokens[iter], ID);
	Predicate pred = Predicate(tokens[iter-1].get_value());
	test(tokens[iter], LEFT_PAREN);
	test(tokens[iter], ID);
	Parameter param = Parameter(tokens[iter-1]);
	pred.add_to_params(param);
	idList(pred);
	test(tokens[iter], RIGHT_PAREN);
	return pred;
}

void Parser::oper(Predicate &pred)
{
	// ADD | MULTIPLY
	if(tokens[iter].get_type() == ADD || tokens[iter].get_type() == MULTIPLY)
	{
		pred.add_to_params(Parameter(tokens[iter]));
		iter++;
		return;
	}
	else
	{
		cout << "Failure!\n" << tokens[iter].toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Parser::expression(Predicate &pred)
{
	//LEFT_PAREN parameter operator parameter RIGHT_PAREN
	test(tokens[iter], LEFT_PAREN);
	parameter(pred);
	oper(pred);
	parameter(pred);
	test(tokens[iter], RIGHT_PAREN);
}

void Parser::parameter(Predicate &pred)
{
	//STRING | ID | expression
	if(tokens[iter].get_type() == LEFT_PAREN)
	{
		expression(pred);
	}
	else if(tokens[iter].get_type() == STRING)
	{
		pred.add_to_params(Parameter(tokens[iter]));
		iter++;
		return;
	}
	else if(tokens[iter].get_type() == ID)
	{
		pred.add_to_params(Parameter(tokens[iter]));
		iter++;
		return;
	}
	else
	{
		cout << "Failure!\n" << tokens[iter].toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Parser::parameterList(Predicate &pred)
{
	//COMMA parameter parameterList | lambda
	if(tokens[iter].get_type() != RIGHT_PAREN)
	{
		test(tokens[iter], COMMA);
		parameter(pred);
		parameterList(pred);
	}
}

void Parser::pred_to_rules(Rule &newRule)
{
	//Prediacte: ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	test(tokens[iter], ID);
	test(tokens[iter], LEFT_PAREN);
	Predicate pred = Predicate(tokens[iter-2].get_value());
	parameter(pred);
	parameterList(pred);
	test(tokens[iter], RIGHT_PAREN);
	newRule.add_to_preds(pred);
}

void Parser::predicateList(Rule &newRule)
{
	//COMMA predicate predicateList | lambda
	if(tokens[iter].get_type() != PERIOD)
	{
		test(tokens[iter], COMMA);
		pred_to_rules(newRule);
		predicateList(newRule);
	}
}

void Parser::rule()
{
	//headPredicate COLON_DASH predicate predicateList PERIOD
	Predicate hPred = headPredicate();
	Rule newRule = Rule(hPred);
	test(tokens[iter], COLON_DASH);
	pred_to_rules(newRule);
	predicateList(newRule);
	test(tokens[iter], PERIOD);
}

void Parser::ruleList()
{
	//rule ruleList | lambda
	if(tokens[iter].get_type() != QUERIES)
	{
		rule();
		ruleList();
	}
	
}

Predicate Parser::predicate()
{
	//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	test(tokens[iter], ID);
	test(tokens[iter], LEFT_PAREN);
	Predicate pred = Predicate(tokens[iter-2].get_value());
	parameter(pred);
	parameterList(pred);
	test(tokens[iter], RIGHT_PAREN);
	return pred;
}

void Parser::query()
{
	//predicate Q_MARK
	Predicate pred = predicate();
	test(tokens[iter], Q_MARK);
}

void Parser::queryList()
{
	//query queryList | lambda
	if(tokens[iter].get_type() != E_O_F)
	{
		query();
		queryList();
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
	ruleList();
	test(tokens[iter],QUERIES);
	test(tokens[iter],COLON);
	query();
	queryList();
	test(tokens[iter],E_O_F);
	cout << "Success!\n";
}