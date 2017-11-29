#pragma once
#include "parameter.h"

using namespace std;

class Predicate
{
private:
	string name;
	vector<Parameter> params;
public:
	Predicate(){}
	Predicate(string name);
	void give_name(string name);
	void add_to_params(Parameter param);
	string toString();
	string get_name();
	Parameter get_param(int i);
	int get_size();
	vector<string> get_params_as_strings();
};