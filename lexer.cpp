#include "Lexer.h"

using namespace std;


/*
Alright, what needs to happen here?
1) 
*/
Lexer::Lexer(string contents)
{

}

string Lexer::get_contents()
{

}

int Lexer::get_num_tokens()
{
	//return number of found tokens; used in the final output.
}

bool Lexer::higher_precedence(string s)
{

}

void Lexer::print_vector()
{
	//Prints the vector that holds the tokens, using toStringToken.
}

int Lexer::run_all_DFA()
{
	//Run them all, shortest to longest?
	//The function just returns the line number. Also, no token uses more than one line.

}


void Lexer::scan()
{
	//contens is the same as result, found in input_stream.
	//Scan actually walks through the whole string, token by token.
	//From here, it find the longest string, sets winningDFA, and 
	//iterates to the next token.
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