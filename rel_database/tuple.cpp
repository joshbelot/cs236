#include "tuple.h"

using namespace std;

Tuple::Tuple()
{
	size = 0;
}

void Tuple::insert(string s)
{
	tuple.push_back(s);
	size++;
}