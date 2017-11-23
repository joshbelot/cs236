#include "predicate.h"

using namespace std;

Predicate::Predicate(string name)
{
	this->name = name;
	vector<Parameter> params;
}

void Predicate::give_name(string name)
{
	this->name = name;
}

void Predicate::add_to_params(Parameter param)
{
	params.push_back(param);
}

string Predicate::toString()
{
	stringstream ss;
	ss << name << "(";
	for(int i = 0; i <params.size(); i++)
	{
		if(i == (params.size() - 1))
		{
			ss << params[i].get_param_value();
		}
		else
		{
			ss << params[i].get_param_value() << ",";
		}
	}
	ss << ")";
	return ss.str();
}

string Predicate::get_name()
{
	return name;
}

Parameter Predicate::get_param(int i)
{
	return params[i];
}

int Predicate::get_size()
{
	return params.size();
}

vector<string> Predicate::get_params_as_strings()
{
	vector<string> param_strings;
	for(int i = 0; i < params.size(); i++)
	{
		param_strings.push_back(params[i].get_param_value());
	}
	return param_strings;
}
