#include "token.h"

Token::Token(type t_type, string t_string, int t_line_num)
{
	this->t_type = t_type;
	this->t_string = t_string;
	this->t_line_num = t_line_num;
}

string Token::toStringType()
{
	switch(t_type)
	{
		case 0:
			return "COMMA";
			break;
		case 1:
			return "PERIOD";
			break;
		case 2:
			return "Q_MARK";
			break;
		case 3:
			return "LEFT_PAREN";
			break;
		case 4:
			return "RIGHT_PAREN";
			break;
		case 5:
			return "COLON";
			break;
		case 6:
			return "COLON_DASH";
			break;
		case 7:
			return "MULTIPLY";
			break;
		case 8:
			return "ADD";
			break;
		case 9:
			return "SCHEMES";
			break;
		case 10:
			return "FACTS";
			break;
		case 11:
			return "RULES";
			break;
		case 12:
			return "QUERIES";
			break;
		case 13:
			return "ID";
			break;
		case 14:
			return "STRING";
			break;
		case 15:
			return "COMMENT";
			break;
		case 16:
			return "WHITESPACE";
			break;
		case 17:
			return "UNDEFINED";
			break;
		case 18:
			return "EOF";
			break;
	}
	return "";
}

string Token::toStringToken()
{
	stringstream ss;
	ss << "(" << toStringType() << ",";
	ss << "\"" << t_string << "\"" << ",";
	ss << t_line_num << ")\n";
	return ss.str();
}

string Token::get_value()
{
	return t_string;
}

type Token::get_type()
{
	return t_type;
}