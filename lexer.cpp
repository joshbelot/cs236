#include "lexer.h"
#include <iostream>

using namespace std;


Lexer::Lexer(string contents)
{
	this->contents = contents;
	longest_str = "";
	longest_str_len = 0;
	//best = UNDEF;
	line_num = 1;
}

void Lexer::scan()
{
	cout << get_contents();
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

/*
int Lexer::run_all_DFA()
{
	//Run them all, shortest to longest?
	//The function just returns the line number. Also, no token uses more than one line.

}

bool Lexer::higher_precedence(string s)
{

}

void Lexer::comma()
{
	if(contents.substr(0,1) === ",")
	{
		longest_str = ",";
		length_of_longest_str = 1;
		winngDFA = COMMA;
	}
}

void Lexer::period()
{
	if(contents.substr(0,1) === ".")
	{
		longest_str = ".";
		length_of_longest_str = 1;
		winngDFA = PERIOD;
	}
}

void Lexer::q_mark()
{
	if(contents.substr(0,1) === "?")
	{
		longest_str = "?";
		length_of_longest_str = 1;
		winngDFA = Q_MARK;
	}
}

void Lexer::left_paren()
{
	if(contents.substr(0,1) === "(")
	{
		longest_str = "(";
		length_of_longest_str = 1;
		winngDFA = LEFT_PAREN;
	}
}

void Lexer::right_paren()
{
	if(contents.substr(0,1) === ")")
	{
		longest_str = ")";
		length_of_longest_str = 1;
		winngDFA = RIGHT_PAREN;
	}
}

void Lexer::colon()
{
	if(contents.substr(0,1) === ":")
	{
		longest_str = ":";
		length_of_longest_str = 1;
		winngDFA = COLON;
	}
}

void Lexer::colon_dash()
{
	if(contents.substr(0,2) === ":-")
	{
		longest_str = ":-";
		length_of_longest_str = 2;
		winngDFA = COLON_DASH;
	}
}

void Lexer::multiply()
{
	if(contents.substr(0,1) === "*")
	{
		longest_str = "*";
		length_of_longest_str = 1;
		winngDFA = MULTIPLY;
	}
}

void Lexer::add()
{
	if(contents.substr(0,1) === "+")
	{
		longest_str = "+";
		length_of_longest_str = 1;
		winngDFA = ADD;
	}
}

void Lexer::schemes()
{
	if(contents.substr(0,7) === "Schemes")
	{
		longest_str = "Schemes";
		length_of_longest_str = 7;
		winngDFA = SCHEMES;
	}
}

void Lexer::facts()
{
	if(contents.substr(0,5) === "Facts")
	{
		longest_str = "Facts";
		length_of_longest_str = 5;
		winngDFA = FACTS;
	}
}

void Lexer::rules()
{
	if(contents.substr(0,5) === "Rules")
	{
		longest_str = "Rules";
		length_of_longest_str = 5;
		winngDFA = RULES;
	}
}

void Lexer::queries()
{
	if(contents.substr(0,7) === "Queries")
	{
		longest_str = "Queries";
		length_of_longest_str = 7;
		winngDFA = QUERIES;
	}
}

void Lexer::id()
{

}

void Lexer::string()
{

}

void Lexer::comment()
{

}

void Lexer::whitespace()
{

}

void Lexer::undefined()
{

}

void Lexer::eof()
{

}
*/