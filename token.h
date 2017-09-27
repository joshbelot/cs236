#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <set>
#include <fstream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum type
{
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	WHITESPACE,
	UNDEFINED,
	EOF,
};

class Token
{
private:
	string t_string;
	type t_type;
	int t_line_num;

public:
	Token(type t_type, string t_string, int t_line_num);
	string toStringType();
	string toStringToken();
	string get_value();
	type get_type();
}