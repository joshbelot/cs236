#pragma once
#include <string>
#include "token.h"

using namespace std;

class Lexer
{
private:
	string contents;
	vector<Token> output_list;
	string longest_str;
	unsigned int longest_str_len;
	type best;
	int line_num;

public:
	Lexer(string contents);
	void scan();
	string get_contents();
	int get_num_tokens();
	void print_num_tokens(int size);
	void print_vector();
	vector<Token> return_vector();
	int token_test();
	bool better(string s);

	void comma();
	void period();
	void q_mark();
	void left_paren();
	void right_paren();
	void colon();
	void colon_dash();
	void multiply();
	void add();
	void schemes();
	void facts();
	void rules();
	void queries();
	void id();
	void str();
	void undef();
	void comment();
	//void multi_line_comment();
	void whitespace();
};