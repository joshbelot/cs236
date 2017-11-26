#include "parameter.h"

using namespace std;

Parameter::Parameter(Token tok)
{
	this->param_value = tok.get_value();
	this->param_type = tok.get_type();
	this->param_string = tok.toStringType();
}

string Parameter::get_param_value()
{
	return param_value;
}

type Parameter::get_param_type()
{
	return param_type;
}

string Parameter::get_param_string()
{
	return param_string;
}