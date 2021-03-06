#pragma once
#include "lexer.h"

using namespace std;

class Parameter
{
private:
	string param_value;
	type param_type;
	string param_string;
public:
	Parameter(Token tok);
	string get_param_value();
	type get_param_type();
	string get_param_string();
};