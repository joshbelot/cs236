#pragma once
//#include "Database.h"
using namespace std;

class Datalog
{
private:
	vector<Token> vT;
	unsigned int index;
	//Database database;

public:
	Datalog(vector<Token> vT);
	Database datalog_parse();
	void match(Token t1, type t2);
	void scheme();
	void schemeList();
	void idList(Predicate &pr);
	void fact();
	void factList();
	void stringList(Predicate &pr);
	void ruleList();
	void rule();
	Predicate headPredicate();
	void predicate(Rule &r);
	Predicate predicate();
	void predicateList(Rule &r);
	void parameter(Predicate &pr);
	void parameterList(Predicate &pr);
	void expression(Predicate &pr);
	void operatr(Predicate &pr);
	void query();
	void queryList();
};