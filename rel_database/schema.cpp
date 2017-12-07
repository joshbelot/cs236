#include "schema.h"

Schema::Schema(){}

Schema::Schema(const vector<string>& scheme_list)
{
	for(auto a : scheme_list)
	{
		this->push_back(a);
	}
}