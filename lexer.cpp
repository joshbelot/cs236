#include "lexer.h"
#include <iostream>

using namespace std;


Lexer::Lexer(string contents)
{
	this->contents = contents;
	longest_str = "";
	longest_str_len = 0;
	best = UNDEF;
	line_num = 1;
}

int Lexer::token_test()
{
	int num = line_num;
	undef();
	comma();
	period();
	q_mark();
	left_paren();
	right_paren();
	colon();
	colon_dash();
	multiply();
	add();
	schemes();
	facts();
	rules();
	queries();
	id();
	str();
	comment();
	whitespace();
	return num;
}

void Lexer::scan()
{
	//Run through the entire string, scanning for tokens and then
	//deleting them from the beginning of the string.
	while(contents.length() > 0)
	{
		longest_str = "";
		longest_str_len = 0;
		best = UNDEF;
		int result_num = token_test();
		string s = longest_str;
		int k = longest_str_len;

		if(k > 0)
		{
			if(best != WHITESPACE)
			{
				if(best == STRING)
				{
					output_list.push_back(Token(best,s,num));
					line_num += str();
				}
			}
		}
	}
}

string Lexer::get_contents()
{
	return contents;
}

int Lexer::get_num_tokens()
{
	return output_list.size();
}

void Lexer::print_vector()
{
	for(int i = 0; i < output_list.size(); i++)
	{
		cout << output_list[i].toStringToken();
	}
}

vector<Token> Lexer::return_vector()
{
	return output_list;
}


//State machines to identify characters
void Lexer::comma()
{
	if(contents.substr(0,1) == ",")
	{
		longest_str = ",";
		longest_str_len = 1;
		best = COMMA;
	}
}

void Lexer::period()
{
	if(contents.substr(0,1) == ".")
	{
		longest_str = ".";
		longest_str_len = 1;
		best = PERIOD;
	}
}

void Lexer::q_mark()
{
	if(contents.substr(0,1) == "?")
	{
		longest_str = "?";
		longest_str_len = 1;
		best = Q_MARK;
	}
}

void Lexer::left_paren()
{
	if(contents.substr(0,1) == "(")
	{
		longest_str = "(";
		longest_str_len = 1;
		best = LEFT_PAREN;
	}
}

void Lexer::right_paren()
{
	if(contents.substr(0,1) == ")")
	{
		longest_str = ")";
		longest_str_len = 1;
		best = RIGHT_PAREN;
	}
}

void Lexer::colon()
{
	if(contents.substr(0,1) == ":")
	{
		longest_str = ":";
		longest_str_len = 1;
		best = COLON;
	}
}

void Lexer::colon_dash()
{
	if(contents.substr(0,2) == ":-")
	{
		longest_str = ":-";
		longest_str_len = 2;
		best = COLON_DASH;
	}
}

void Lexer::multiply()
{
	if(contents.substr(0,1) == "*")
	{
		longest_str = "*";
		longest_str_len = 1;
		best = MULTIPLY;
	}
}

void Lexer::add()
{
	if(contents.substr(0,1) == "+")
	{
		longest_str = "+";
		longest_str_len = 1;
		best = ADD;
	}
}

void Lexer::schemes()
{
	if(contents.substr(0,7) == "Schemes")
	{
		longest_str = "Schemes";
		longest_str_len = 7;
		best = SCHEMES;
	}
}

void Lexer::facts()
{
	if(contents.substr(0,5) == "Facts")
	{
		longest_str = "Facts";
		longest_str_len = 5;
		best = FACTS;
	}
}

void Lexer::rules()
{
	if(contents.substr(0,5) == "Rules")
	{
		longest_str = "Rules";
		longest_str_len = 5;
		best = RULES;
	}
}

void Lexer::queries()
{
	if(contents.substr(0,7) == "Queries")
	{
		longest_str = "Queries";
		longest_str_len = 7;
		best = QUERIES;
	}
}

void Lexer::id()
{

}

int Lexer::str()
{
	return 1;
}

int Lexer::comment()
{
	return 1;
}

int Lexer::undef()
{
	return 1;
}

void Lexer::whitespace()
{

}

/*
bool Lexer::better(string s)
{

}


void Lexer::eof()
{

}
*/