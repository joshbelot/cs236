#include "predicate.h"

using namespace std;

Predicate(string name)
{
	this->name = name;
	vector<Parameter> params;
}

void give_name(string name)
{
	this->name = name;
}

void add_to_params(Parameter param)
{
	params.push_back(param);
}

string toString()
{
	stringstream ss;
	ss << name << "(";
	for(int i = 0; i <params.size(); i++)
	{
		if(i == (params.size() - 1))
		{
			ss << params[i].get_value();
		}
		else
		{
			ss << params[i].get_value(); << ",";
		}
	}
	ss << ")";
	return ss.str();
}

string get_name()
{
	return name;
}

Paramter get_param(int i)
{
	return params[i];
}

int get_size()
{
	return params.size();
}

vector<string> get_params_as_strings()
{
	vector<string> param_strings;
	for(int i = 0; i < params.size(); i++)
	{
		param_strings.push_back(params[i].get_value());
	}
	return param_strings;
}
