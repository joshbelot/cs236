#pragma once
#include <vector>
#include <string>

using namespace std;

class Tuple:public vector<string>
{
public:
	Tuple();
	Tuple(const vector<string>& tuple_list);
	string toString();
}