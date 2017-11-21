#include "Datalog.h"

using namespace std;

Datalog::Datalog(vector<Token> vT)
{
	this->vT = vT;
	index = 0;
	database = Database();
}

void Datalog::match(Token t1, type t2)//example: match(vT[index],SCHEMES)
{
	if(t1.get_type() == t2)
	{
		index++;
		return;
	}
	else
	{
		cout << "Failure!\n  " << t1.toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Datalog::scheme()
{
	match(vT[index],ID);//name, start making a predicate
	Predicate pr = Predicate(vT[index-1].get_value());
	match(vT[index],LEFT_PAREN);
	match(vT[index],ID);//contents, start the list of parameters
	Parameter pa = Parameter(vT[index-1]);
	pr.add_to_parameters(pa);
	idList(pr);
	match(vT[index],RIGHT_PAREN);
	database.add_to_schemes(pr);
}

void Datalog::schemeList()
{
	if(vT[index].get_type() != FACTS)
	{
		scheme();
		schemeList();
	}
}

void Datalog::idList(Predicate &pr)
{
	if(vT[index].get_type() != RIGHT_PAREN)
	{
		match(vT[index],COMMA);
		match(vT[index],ID);//add to the parameter vector
		Parameter pa = Parameter(vT[index-1]);
		pr.add_to_parameters(pa);
		idList(pr);
	}
}

void Datalog::fact()
{
	match(vT[index],ID);
	Predicate pr = Predicate(vT[index-1].get_value());
	match(vT[index],LEFT_PAREN);
	match(vT[index],STRING);
	Parameter pa = Parameter(vT[index-1]);
	pr.add_to_parameters(pa);
	database.add_to_domain(pa.get_value());
	stringList(pr);
	match(vT[index],RIGHT_PAREN);
	match(vT[index],PERIOD);
	database.add_to_facts(pr);
}

void Datalog::factList()
{
	if(vT[index].get_type() != RULES)
	{
		fact();
		factList();
	}
}

void Datalog::stringList(Predicate &pr)
{
	if(vT[index].get_type() != RIGHT_PAREN)
	{
		match(vT[index],COMMA);
		match(vT[index],STRING);
		Parameter pa = Parameter(vT[index-1]);
		pr.add_to_parameters(pa);
		database.add_to_domain(pa.get_value());
		stringList(pr);
	}
}

Predicate Datalog::predicate()
{
	match(vT[index],ID);
	match(vT[index],LEFT_PAREN);
	Predicate pr = Predicate(vT[index-2].get_value());
	parameter(pr);
	parameterList(pr);
	match(vT[index],RIGHT_PAREN);
	return pr;
}

void Datalog::predicate(Rule &r)
{
//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	match(vT[index],ID);
	match(vT[index],LEFT_PAREN);
	Predicate pr = Predicate(vT[index-2].get_value());
	parameter(pr);
	parameterList(pr);
	match(vT[index],RIGHT_PAREN);
	r.add_to_body(pr);
}

void Datalog::predicateList(Rule &r)
{
//predicateList	->	COMMA predicate predicateList | lambda
	if(vT[index].get_type() != PERIOD)
	{
		match(vT[index],COMMA);
		predicate(r);
		predicateList(r);
	}
}

void Datalog::parameter(Predicate &pr)
{
//parameter	->	STRING | ID | expression
	if(vT[index].get_type() == LEFT_PAREN)
	{
		expression(pr);
	}
	else if(vT[index].get_type() == STRING)
	{
		pr.add_to_parameters(Parameter(vT[index]));
		index++;
		return;
	}
	else if(vT[index].get_type() == ID)
	{
		pr.add_to_parameters(Parameter(vT[index]));
		index++;
		return;
	}
	else
	{
		cout << "Failure!\n  " << vT[index].toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Datalog::parameterList(Predicate &pr)
{
//parameterList	-> 	COMMA parameter parameterList | lambda
	if(vT[index].get_type() != RIGHT_PAREN)
	{
		match(vT[index],COMMA);
		parameter(pr);
		parameterList(pr);
	}
}

void Datalog::expression(Predicate &pr)
{
//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	match(vT[index],LEFT_PAREN);
	parameter(pr);
	operatr(pr);
	parameter(pr);
	match(vT[index],RIGHT_PAREN);
}

void Datalog::operatr(Predicate &pr)
{
//operator	->	ADD | MULTIPLY
	if(vT[index].get_type() == ADD || vT[index].get_type() == MULTIPLY)
	{
		pr.add_to_parameters(Parameter(vT[index]));
		index++;
		return;
	}
	else
	{
		cout << "Failure!\n  " << vT[index].toStringToken();
		exit(EXIT_FAILURE);
	}
}

void Datalog::ruleList()
{
	if(vT[index].get_type() != QUERIES)
	{
		rule();
		ruleList();
	}
}

void Datalog::rule()
{
	Predicate pr1 = headPredicate();
	Rule r = Rule(pr1);
	match(vT[index],COLON_DASH);
	predicate(r);//add_to_body
	predicateList(r);
	match(vT[index],PERIOD);
	database.add_to_rules(r);
}

Predicate Datalog::headPredicate()
{
	match(vT[index],ID);
	Predicate pr = Predicate(vT[index-1].get_value());
	match(vT[index],LEFT_PAREN);
	match(vT[index],ID);
	Parameter pa = Parameter(vT[index-1]);
	pr.add_to_parameters(pa);
	idList(pr);
	match(vT[index],RIGHT_PAREN);
	return pr;
}

void Datalog::query()
{
//query	        ->      predicate Q_MARK
	Predicate pr = predicate();
	match(vT[index],Q_MARK);
	database.add_to_queries(pr);
}

void Datalog::queryList()
{
//queryList	->	query queryList | lambda
	if(vT[index].get_type() != ENDOFFILE)
	{
		query();
		queryList();
	}
}

Database Datalog::datalog_parse()
{
	match(vT[index],SCHEMES);
	match(vT[index],COLON);
	scheme();
	schemeList();
	match(vT[index],FACTS);
	match(vT[index],COLON);
	factList();
	match(vT[index],RULES);
	match(vT[index],COLON);
	ruleList();
	match(vT[index],QUERIES);
	match(vT[index],COLON);
	query();
	queryList();
	match(vT[index],ENDOFFILE);
	return database;
}