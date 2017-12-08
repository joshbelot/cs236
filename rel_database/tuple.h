#pragma once
#include <vector>
#include <string>

using namespace std;

class Tuple
{
public:
	vector<string> tuple;
	int size;
	Tuple();
	void insert(string s);
	bool operator< (const Tuple& r) const
	{
		return tuple < r.tuple;
	}
};