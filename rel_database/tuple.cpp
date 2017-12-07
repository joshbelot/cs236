#include "tuple.h"

Tuple::Tuple(){}

Tuple::Tuple(const vector<string>& tuple_list)
{
	for(auto a : tuple_list)
	{
		this->push_back(a);	
	}
}

string Tuple::toString()
{
	string s = "";
	for(auto t : (*this))
	{
		s += t + "\t";
	}
	s.pop_back();
	return s;
}