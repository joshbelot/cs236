#include "parser.h"
#include <vector>

using namespace std;

Parser::Parser(vector<Token> tokens)
{
	this->tokens = tokens;
	iter = 0;
	numSchemes = 0;
	numFacts = 0;
	numRules = 0;
	numQuer = 0;
	numDomain = 0;
	string schemes = "";
	string facts = "";
	string rules = "";
	string quers = "";
	vector<string> domains;
}

void Parser::test(Token tok1, type tok2)
{
	//cout << tok1.toStringType() << " and " << tok2 << "\n";
	if(tok1.get_type() == tok2)
	{
		iter++;
		return;
	}
	else if(tok1.get_type() == COMMENT)
	{
		iter++;
		test(tokens[iter], tok2);
	}
	else
	{
		//cout << tok1.toStringType() << " and " << tok2 << "\n";
		cout << "Failure!\n" << tok1.toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Parser::idList(Predicate &preds, string &section)
{
	//COMMA ID idList | lambda
	if(tokens[iter].get_type() != RIGHT_PAREN)
	{
		test(tokens[iter], COMMA);
		add_to_section(tokens[iter-1], section);
		//cout << "COMMA: " << tokens[iter-1].toStringToken() << "\n";
		test(tokens[iter], ID);
		add_to_section(tokens[iter-1], section);
		//cout << "ID: " << tokens[iter-1].toStringToken() << "\n";
		Parameter param = Parameter(tokens[iter-1]);
		preds.add_to_params(param);
		idList(preds, section);
	}
}

void Parser::scheme()
{
	//ID LEFT_PAREN ID idList RIGHT_PAREN
	schemes+="  ";
	test(tokens[iter], ID);
	Predicate preds = Predicate(tokens[iter-1].get_value());
	add_to_section(tokens[iter-1], schemes);
	test(tokens[iter], LEFT_PAREN);
	add_to_section(tokens[iter-1], schemes);
	test(tokens[iter], ID);
	Parameter param = Parameter(tokens[iter-1]);
	preds.add_to_params(param);
	add_to_section(tokens[iter-1], schemes);
	idList(preds, schemes);
	test(tokens[iter], RIGHT_PAREN);
	add_to_section(tokens[iter-1], schemes);
	schemes+="\n";
	numSchemes++;
}

void Parser::schemeList()
{
	if(tokens[iter].get_type() != COMMENT)
	{
		//scheme schemeList | lamda
		if(tokens[iter].get_type() != FACTS)
		{
			scheme();
			schemeList();
		}
	}
	else
	{
		if(tokens[iter+1].get_type() != FACTS)
		{
			scheme();
			schemeList();
		}
	}
}

void Parser::stringList(Predicate &preds, string &section)
{
	//COMMA STRING stringList | lambda
	if(tokens[iter].get_type() != RIGHT_PAREN)
	{
		test(tokens[iter], COMMA);
		add_to_section(tokens[iter-1], section);
		test(tokens[iter], STRING);
		string dom = tokens[iter-1].get_value();
		cout << dom << "\n";
		//This is the line that causes the trouble.
		//domains.push_back(dom);
		add_to_section(tokens[iter-1], section);
		Parameter param = Parameter(tokens[iter-1]);
		preds.add_to_params(param);
		stringList(preds, section);
	}
}

void Parser::fact()
{
	// ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	facts+="  ";
	test(tokens[iter], ID);
	Predicate preds = Predicate(tokens[iter-1].get_value());
	add_to_section(tokens[iter-1], facts);
	test(tokens[iter], LEFT_PAREN);
	add_to_section(tokens[iter-1], facts);
	test(tokens[iter], STRING);
	Parameter param = Parameter(tokens[iter-1]);
	preds.add_to_params(param);
	add_to_section(tokens[iter-1], facts);
	stringList(preds, facts);
	test(tokens[iter], RIGHT_PAREN);
	add_to_section(tokens[iter-1], facts);
	test(tokens[iter], PERIOD);
	add_to_section(tokens[iter-1], facts);
	facts+="\n";
	numFacts++;
}

void Parser::factList()
{
	if(tokens[iter].get_type() != COMMENT)
	{
		if(tokens[iter].get_type() != RULES)
		{
			fact();
			factList();
		}
	}
	else
	{
		if(tokens[iter+1].get_type() != RULES)
		{
			fact();
			factList();
		}
	}
}

Predicate Parser::headPredicate()
{
	//ID LEFT_PAREN ID idList RIGHT_PAREN
	test(tokens[iter], ID);
	add_to_section(tokens[iter-1], rules);
	Predicate pred = Predicate(tokens[iter-1].get_value());
	test(tokens[iter], LEFT_PAREN);
	add_to_section(tokens[iter-1], rules);
	test(tokens[iter], ID);
	add_to_section(tokens[iter-1], rules);
	Parameter param = Parameter(tokens[iter-1]);
	pred.add_to_params(param);
	idList(pred, rules);
	test(tokens[iter], RIGHT_PAREN);
	add_to_section(tokens[iter-1], rules);
	return pred;
}

void Parser::oper(Predicate &pred)
{
	// ADD | MULTIPLY
	if(tokens[iter].get_type() == ADD || tokens[iter].get_type() == MULTIPLY)
	{
		pred.add_to_params(Parameter(tokens[iter]));
		add_to_section(tokens[iter], rules);
		iter++;
		return;
	}
	else
	{
		cout << "Failure!\n" << tokens[iter].toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Parser::expression(Predicate &pred, string &section)
{
	//LEFT_PAREN parameter operator parameter RIGHT_PAREN
	test(tokens[iter], LEFT_PAREN);
	add_to_section(tokens[iter-1], section);
	parameter(pred, section);
	oper(pred);
	parameter(pred, section);
	test(tokens[iter], RIGHT_PAREN);
	add_to_section(tokens[iter-1], section);
}

void Parser::parameter(Predicate &pred, string &section)
{
	//STRING | ID | expression
	if(tokens[iter].get_type() == LEFT_PAREN)
	{
		expression(pred, section);
	}
	else if(tokens[iter].get_type() == STRING)
	{
		pred.add_to_params(Parameter(tokens[iter]));
		add_to_section(tokens[iter], section);
		iter++;
		return;
	}
	else if(tokens[iter].get_type() == ID)
	{
		pred.add_to_params(Parameter(tokens[iter]));
		add_to_section(tokens[iter], section);
		iter++;
		return;
	}
	else
	{
		cout << "Failure!\n" << tokens[iter].toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Parser::parameterList(Predicate &pred, string &section)
{
	//COMMA parameter parameterList | lambda
	if(tokens[iter].get_type() != RIGHT_PAREN)
	{
		test(tokens[iter], COMMA);
		add_to_section(tokens[iter-1], section);
		parameter(pred, section);
		parameterList(pred, section);
	}
}

void Parser::pred_to_rules(Rule &newRule)
{
	//Prediacte: ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	test(tokens[iter], ID);
	add_to_section(tokens[iter-1], rules);
	test(tokens[iter], LEFT_PAREN);
	add_to_section(tokens[iter-1], rules);
	Predicate pred = Predicate(tokens[iter-2].get_value());
	parameter(pred, rules);
	parameterList(pred, rules);
	test(tokens[iter], RIGHT_PAREN);
	add_to_section(tokens[iter-1], rules);
	newRule.add_to_preds(pred);
}

void Parser::predicateList(Rule &newRule)
{
	//COMMA predicate predicateList | lambda
	if(tokens[iter].get_type() != PERIOD)
	{
		test(tokens[iter], COMMA);
		add_to_section(tokens[iter-1], rules);
		pred_to_rules(newRule);
		predicateList(newRule);
	}
}

void Parser::rule()
{
	//headPredicate COLON_DASH predicate predicateList PERIOD
	rules+="  ";
	Predicate hPred = headPredicate();
	Rule newRule = Rule(hPred);
	rules+=" ";
	test(tokens[iter], COLON_DASH);
	add_to_section(tokens[iter-1], rules);
	rules+=" ";
	pred_to_rules(newRule);
	predicateList(newRule);
	test(tokens[iter], PERIOD);
	add_to_section(tokens[iter-1], rules);
	rules+="\n";
	numRules++;
}

void Parser::ruleList()
{
	//rule ruleList | lambda
	if(tokens[iter].get_type() != COMMENT)
	{
		if(tokens[iter].get_type() != QUERIES)
		{
			rule();
			ruleList();
		}
	}
	else
	{
		if(tokens[iter+1].get_type() != QUERIES)
		{
			rule();
			ruleList();
		}
	}	
}

Predicate Parser::predicate(string &section)
{
	//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	test(tokens[iter], ID);
	add_to_section(tokens[iter-1], section);
	test(tokens[iter], LEFT_PAREN);
	add_to_section(tokens[iter-1], section);
	Predicate pred = Predicate(tokens[iter-2].get_value());
	parameter(pred, section);
	parameterList(pred, section);
	test(tokens[iter], RIGHT_PAREN);
	add_to_section(tokens[iter-1], section);
	return pred;
}

void Parser::query()
{
	//predicate Q_MARK
	quers+="  ";
	Predicate pred = predicate(quers);
	test(tokens[iter], Q_MARK);
	add_to_section(tokens[iter-1], quers);
	quers+="\n";
	numQuer++;
}

void Parser::queryList()
{
	//query queryList | lambda
	if(tokens[iter].get_type() != COMMENT)
	{
		if(tokens[iter].get_type() != E_O_F)
		{
			query();
			queryList();
		}
	}
	else
	{
		if(tokens[iter+1].get_type() != E_O_F)
		{
			query();
			queryList();
		}
	}
	
}

void Parser::datalog_parse()
{
	test(tokens[iter], SCHEMES);
	test(tokens[iter], COLON);
	scheme();
	schemeList();
	test(tokens[iter], FACTS);
	test(tokens[iter], COLON);
	factList();
	test(tokens[iter], RULES);
	test(tokens[iter], COLON);
	ruleList();
	test(tokens[iter], QUERIES);
	test(tokens[iter], COLON);
	query();
	queryList();
	test(tokens[iter], E_O_F);
	cout << "Success!\n";
	numDomain = domains.size();
	printDatalog();
}

void Parser::add_to_section(Token tok, string &content)
{
	if(tok.get_type() != COMMENT)
	{
		content+=tok.get_value();
	}
}

void Parser::printDatalog()
{
	cout << "Schemes(" << numSchemes << "):\n";
	cout << schemes;
	cout << "Facts(" << numFacts << "):\n";
	cout << facts;
	cout << "Rules(" << numRules << "):\n";
	cout << rules;
	cout << "Queries(" << numQuer << "):\n";
	cout << quers;
	cout << "Domain(" << numDomain << "):\n";
	//cout << domains;
}