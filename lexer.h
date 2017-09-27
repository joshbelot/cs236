#pragma once
#include "token.h"

using namespace std;

class Lexer
{
private:
	string contents;
	vector<Token> output_list;
	string longest_str;
	unsigned int length_of_longest_str;
	type winningDFA;
	int line_num;

public:
	Lexer(string contents);
	string get_contents();
	int get_num_tokens();
	bool higher_precendence(string s);
	void print_vector();
	int run_all_DFA();
	void scan();
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
	int str();
	int comment();
	void scomment();
	int mcomment();
	void whitespace();
	int undef();
	void add_to_line_count(char c, int &j);
	vector<Token> return_vector();
};