#include "lexer.h"
#include <iostream>

using namespace std;

/*
Missing the following:
Comment

Minor issues:
ID uses goto statements; refactor?
*/

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
	single_line_comment();
	multi_line_comment();
	whitespace();
	return num;
}

//Check between ID and anything else. ID has lowest priority.
bool Lexer::better(string s)
{
	if(longest_str == "Queries" || longest_str == "Rules" || longest_str == "Facts" || longest_str == "Schemes")
	{
		//If the current longest string is higher precedence AND 
		//	potential ID is not longer than longest string, then 
		//	it's not an ID at all.
		if(s.size() > longest_str_len)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
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
					output_list.push_back(Token(best,s,result_num));
				}
				else if(best == COMMENT)
				{
					output_list.push_back(Token(best,s,result_num));
				}
				else if(best == UNDEF)
				{
					output_list.push_back(Token(best,s,result_num));
					line_num += undef();
				}
				else
				{
					output_list.push_back(Token(best,s,result_num));
				}
			}
			else
			{
				line_num++;
			}
			//Remove the token that was just parsed.
			for(int i = 0; i < k; i++)
			{
				contents.erase(contents.begin());
			}
		}
		//Remove whitespace token found at beginning of string
		//and do nothing else
		else
		{
			contents.erase(contents.begin());
		}
	}
	//When contents.length <= 0, add the endOfFile token to the vector
	line_num--;
	output_list.push_back(Token(E_O_F,"",line_num));

	print_vector();
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
	//States of the automaton.
	enum state
	{
		start,
		accept
	};
	state s = start;
	stringstream ss;
	char c;
	for(int i = 0; i < contents.size(); i++)
	{
		//c advances to next char with each iteration
		c = contents[i];

		//The actual state machine
		switch(s)
		{
			case start:
				//ID's start with alpha character. If c is alpha, accept the ID
				// and read it into the string stream.
				if(isalpha(c))
				{
					ss << c;
					s = accept;
				}
				else
				{
					//break out of the for loop.
					//Is there a better way to do this than exit?
					goto exit;
				}
				break;
			case accept:
				//ID's are a letter followed by any string of letters and numbers.
				//While the input is either of these, keep reading them into ss.
				if(isalpha(c) || isdigit(c))
				{
					ss << c;
				}
				else
				{
					//break out of the for loop.
					goto exit;
				}
				break;
		}
	}

	//guide point for the gotos used above
	exit:

	string id_token = ss.str();

	//If s was accepted and there isn't a better token being read,
	//	then accept a new token.
	if(s == accept && !better(id_token))
	{
		longest_str = id_token;
		longest_str_len = longest_str.size();
		best = ID;
	}
}

void Lexer::str()
{
	enum state
	{
		start,
		undefined,
		accept,
		fail
	};

	state s = start;
	stringstream ss;
	char c;

	for(int i = 0; i < contents.size(); i++)
	{
		c = contents[i];
		switch(s)
		{
			case start:
				if (c == '\'')
				{
					s = undefined;
					ss << c;
				}
				else
				{
					goto exit;
				}
				break;
			case undefined:
				if(c == '\'')
				{
					//Second quote closes the string.
					s = accept;
				}
				if(c == '\n')
				{
					line_num++;
				}
				ss << c;
				break;
			case accept:
				if(c == '\'')
				{
					s = undefined;
					ss << c;
				}
				else
				{
					goto exit;
				}
				break;
			case fail:
				break;
		}
	}
	exit:
	string output = ss.str();
	if(s == undefined)
	{
		longest_str = output;
		longest_str_len = longest_str.size();
		best = UNDEF;
	}
	if(s == accept)
	{
		longest_str = output;
		longest_str_len = longest_str.size();
		best = STRING;
	}
}

void Lexer::comment()
{
	//States of the automaton.
	enum state
	{
		start,
		multi,
		undef,
		accept,
		accept_multi
	};
	state s = start;
	stringstream ss;
	char c;
	char cc;
	for(int i = 0; i < contents.size(); i++)
	{
		//c advances to next char with each iteration
		c = contents[i];
		cc = contents[i + 1];

		//The actual state machine
		switch(s)
		{
			case start:
				//ID's start with alpha character. If c is alpha, accept the ID
				// and read it into the string stream.
				if(c == '#' && cc != '|')
				{
					ss << c;
					s = accept;
				}
				else if(c == '#' && cc == '|')
				{
					ss << c;
					ss << cc;
					i++;
					s = accept_multi;
				}
				else
				{
					//break out of the for loop.
					//Is there a better way to do this than exit?
					goto exit;
				}
				break;
			case accept:
				//ID's are a letter followed by any string of letters and numbers.
				//While the input is either of these, keep reading them into ss.
				if(c != '\n')
				{
					ss << c;
				}
				else
				{
					//break out of the for loop.
					goto exit;
				}
				break;
			case accept_multi:
				if(c == '|' && cc == '#')
				{
					ss << c;
					ss << cc;
					goto exit;
				}
				else if()
		}
	}

	//guide point for the gotos used above
	exit:

	string id_token = ss.str();

	//If s was accepted and there isn't a better token being read,
	//	then accept a new token.
	if(s == accept)
	{
		longest_str = id_token;
		longest_str_len = longest_str.size();
		best = COMMENT;
	}	
}

void Lexer::multi_line_comment()
{
	enum state
	{
		start,
		undefined,
		accept,
		fail
	};

	state s = start;
	stringstream ss;
	char c;
	char cc;

	for(int i = 0; i < contents.size(); i++)
	{
		c = contents[i];
		cc = contents[i+1];
		switch(s)
		{
			case start:
				if (c == '#' && cc == '|')
				{
					s = undefined;
					ss << c;
					ss << cc;
					i++;
				}
				else
				{
					goto exit;
				}
				break;
			case undefined:
				if(c == '|' && cc == '#')
				{
					//Second |# closes the multi-line comment.
					s = accept;
				}
				if(c == '\n')
				{
					line_num++;
				}
				ss << c;
				break;
			case accept:
				if(c == '|' && cc == '#')
				{
					s = undefined;
					ss << c;
				}
				else
				{
					goto exit;
				}
				break;
			case fail:
				break;
		}
	}
	exit:
	string output = ss.str();
	if(s == undefined)
	{
		longest_str = output;
		longest_str_len = longest_str.size();
		best = UNDEF;
	}
	if(s == accept)
	{
		longest_str = output;
		longest_str_len = longest_str.size();
		best = COMMENT;
	}	
}

int Lexer::undef()
{
	return 1;
}

void Lexer::whitespace()
{
	if(contents[0] == '\n')
	{
		longest_str = "";
		longest_str_len = 1;
		best = WHITESPACE;
	}
}

/*
void Lexer::eof()
{

}
*/