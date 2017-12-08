// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
// The database class pulls from here and the table class to perform the queries. 
#pragma once
#include "tuple.h"
#include "pair.h"
#include <set>

using namespace std;

Relation::Relation(string name)
{
	this->name = name;
}

Relation::Relation(string name, vector<string> schema, set<Tuple> tuples)
{
	this->name = name;
	this->schema = schema;
	this->tuples = tuples;
}

void Relation::insert(Tuple t)
{
	tuples.insert(t);
}

void Relation::print()
{

}

void Relation::add_to_schema(string s)
{
	schema.push_back(s);
}

void Relation::rename(vector<string> attributes)
{
	assert (attributes.size() == schema.size());
	schema = attributes;
}

Relation Relation::project(vector<string> attributes)
{
	vector<string> new_schema = attributes;
	vector<int> indexes = return_indexes(attributes);
	set<Tuple> new_tuples;
	for(Tuple t : tuples)
	{
		Tuple new_tuple = Tuple();
		for(int i = 0; i < index.size(); i++)
		{
			new_tuple.insert(t.tuple[indexes[i]]);
		}
		new_tuples.insert(new_tuple);
	}
	return Relation(name, new_schema, new_tuples);
}

Relation Relation::select1(string attribute, string value)
{
	int index = return_index(attribute);
	set<Tuple> new_tuples;
	for(Tuple t : tuples)
	{
		if(t.tuple[index] == value)
		{
			new_tuples.insert(t);
		}
	}
	return Relation(name, schema, new_tuples);
}

Relation Relation::select2(string attribute1, string attribute2)
{
	int index1 = return_index(attributes1);
	int index2 = return_index(attribures2);
	set<Tuple> new_tuples;
	for(Tuple t : tuples)
	{
		if(t.tuple[index1] == t.tuple[index2])
		{
			new_tuples.insert(t);
		}
	}
	return Relation(name, schema, new_tuples);
}

vector<int> Relation::return_indexes(vector<string> attributes)
{
	vector<int> return_vector;
	for(int i = 0; i < attributes.size(); i++)
	{
		for(int j = 0; j < schema.size(); j++)
		{
			if(attributes[i] == schema[j])
			{
				return_vector.push_back(j);
				break;
			}
		}
	}
	return return_vector;
}

int Relation::return_index(string attribute)
{
	for(int i = 0; i < schema.size(); i++)
	{
		if(schema[i] == attribute)
		{
			return i;
		}
	}
	return -1;
}

vector<Pair> Relation::shared(const vector<string>& schema1, const vector<string>& schema2)
{
	vector<Pair> pairs;
	for(int i = 0; i < schema1.size(); i++)
	{
		for(int j = 0; j < schema2.size(); j++)
		{
			if(schema1[i] == schema2[j])
			{
				pairs.push_back(Pair(schema1[i],i));
				pairs.push_back(Pair(schema2[j],j));
			}
		}
	}
	return pairs;
}

vector<string> Relation::make_new_schema(const vector<string>& schema1, const vector<string>& schema2)
{
	vector<string> new_schema;
	for(int i = 0; i < schema1.size(); i++)
	{
		new_schema.push_back(schema1[i]);
	}
	for(int j = 0; j < schema2.size(); j++)
	{
		if(!is_found(new_schema, schema2[j]))
		{
			new_schema.push_back(schema2[j]);
		}
	}
	return new_schema;
}

bool Relation::compatible(Tuple t1, Tuple t2, const vector<Pair>& pairs)
{
	for(int i = 0; i < pairs.size(); i = i + 2)
	{
		if(t1.tuple[pairs[i].index] != t2.tuple[pairs[i+1].index])
		{
			return false;
		}
	}
	return true;
}

Tuple Relation::merge_tuples(Tuple t1, Tuple t2, const vector<Pair>& pairs, const vector<string>& new_schema)
{
	Tuple t = Tuple();
	for(int i = 0; i < t1.size; i++)
	{
		t.insert(t1.tuple[i]);
	}
	for(int j = 0; j < t2.size; j++)
	{
		bool is_good = true;
		for(int k = 1; k < pairs.size(); k = k + 2)
		{
			if(j == pairs[k].index)
			{
				is_good = false;
			}
		}
		if(is_good)
		{
			t.insert(t2.tuple[j]);
		}
	}
	assert(t.size == new_schema.size());
	return t;
}

Relation Relation::join(const Relation& r1, const Relation& r2)
{
	Relation r = Relation("joined");
	vector<Pair> pairs = shared(r1.schema,r2.schema);
	vector<string> new_schema = make_new_schema(r1.schema,r2.schema);
	r.schema = new_schema;
	for(Tuple t1 : r1.tuples)
	{
		for(Tuple t2 : r2.tuples)
		{
			if(compatible(t1, t2, pairs))
			{
				r.insert(merge_tuples(t1, t2, paris, new_schema));
			}
		}
	}
	return r;
}

bool Relation::is_found(const vector<string>& v, string s)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i] == s)
		{
			return true;
		}
	}
	return false;
}