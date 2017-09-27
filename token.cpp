#include "Token.h"

Token::Token(type t_type, string t_string, int t_line_num)
{
	this->t_type = t_type;
	this->t_string = t_string;
	this->t_line_num = t_lin_num;
}

string Token::toStringType()
{
	switch(t_type)
	{
		case COMMA:
			return "COMMA";
			break;
		case PERIOD:
			return "PERIOD";
			break;
		case Q_MARK:
			return "Q_MARK";
			break;
		case LEFT_PAREN:
			return "LEFT_PAREN";
			break;
		case RIGHT_PAREN:
			return "RIGHT_PAREN";
			break;
		case COLON:
			return "COLON";
			break;
		case COLON_DASH:
			return "COLON_DASH";
			break;
		case MULTIPLY:
			return "MULTIPLY";
			break;
		case ADD:
			return "ADD";
			break;
		case SCHEMES:
			return "SCHEMES";
			break;
		case FACTS:
			return "FACTS";
			break;
		case RULES:
			return "RULES";
			break;
		case QUERIES:
			return "QUERIES";
			break;
		case ID:
			return "ID";
			break;
		case STRING:
			return "STRING";
			break;
		case COMMENT:
			return "COMMENT";
			break;
		case WHITESPACE:
			return "WHITESPACE";
			break;
		case UNDEFINED:
			return "UNDEFINED";
			break;
		case EOF:
			return "EOF";
			break;
	}
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