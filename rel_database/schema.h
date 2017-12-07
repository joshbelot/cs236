#pragma once
#include <vector>
#include <string>

using namespace std;

//Schema IS a vector. Anything you can do with a vector, you can do with a schema.
class Schema:public vector<string>
{
public:
	Schema();
	Schema(const vector<string>& scheme_list);
};