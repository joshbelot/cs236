// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
#include "relation.h"
#include <assert.h>
#include <iostream>

using namespace std;

Relation::Relation(string name)
{
	this->name = name;
}

Relation::Relation(string name, vector<string> schema, set<Tuple> tups)
{
	this->name = name;
	this->schema = schema;
	this->tups = tups;
}

void Relation::insert(Tuple t)
{
	tups.insert(t);
}

void Relation::add_to_schema(string s)
{
	schema.push_back(s);
}

Relation Relation::select1(string attrib, string val)
{
	//find where a tuple has the correct value.
	int index = return_index(attrib);
	set<Tuple> new_tups;
	for(Tuple t : tups)
	{
		if(t.tuple[index] == val)
		{
			new_tups.insert(t);
		}
	}
	return Relation(name, schema, new_tups);
}

Relation Relation::select2(string attrib1, string attrib2)
{
	int index1 = return_index(attrib1);
	int index2 = return_index(attrib2);
	set<Tuple> new_tups;
	for(Tuple t: tups)
	{
		if(t.tuple[index1] ==t.tuple[index2])
		{
			new_tups.insert(t);
		}
	}
	return Relation(name, schema, new_tups);
}

Relation Relation::project(vector<string> attribs)
{
  vector<string> new_schema = attribs;
  vector<int> indexes = return_indexes(attribs);
  set<Tuple> new_tuples;
  for(Tuple t : tups)
  {
    Tuple new_tuple = Tuple();
    for(int i = 0; i < indexes.size(); i++)
    {
		new_tuple.insert(t.tuple[indexes[i]]);
    }
    new_tuples.insert(new_tuple);
  }
  return Relation(name, new_schema, new_tuples);
}

void Relation::rename(vector<string> attribs)
{
	//Rename changes the schema/sets the name for the columns results table.
	//assuming the two vectors are the same size...
	assert (attribs.size() == schema.size());
	schema = attribs;
}

vector<int> Relation::return_indexes(vector<string> attribs)
{
	vector<int> return_vector;
	for(int i = 0; i < attribs.size(); i++)
	{
		for(int j = 0; j < schema.size(); j++)
		{
			if(attribs[i] == schema[j])
			{
				return_vector.push_back(j);
				break;
			}
		}
	}
	return return_vector;
}

int Relation::return_index(string attrib)
{
	//Make sure the schema are all correct before we operate.
	for(int i =0; i < schema.size(); i++)
	{
		if(schema[i] == attrib)
		{
			return i;
		}
	}
	return -1;
}

/*
vector<Pair> Relation::shared(const vector<string>& schema1, const vector<string>& schema2)
{

}

vector<string> Relation::make_new_schema(const vector<string>& schema1, const vector<string>& schema2)
{

}

bool Relation::compatible(Tuple t1, Tuple t2, const vector<Pair>& pairs)
{

}

Tuple Relation::merge_tuples(Tuple t1, Tuple t2, const vector<Pair>& pairs, const vector<string>& new_schema)
{

}

Relation Relation::join(const Relation& r1, const Relation& r2)
{

}

bool Relation::is_found(const vector<string>& v, string s)
{

}
*/

void Relation::print()
{
	cout << name << endl;
	for(string e : schema)
	{
		cout << e << " ";
	}
	cout << endl;
	for(Tuple e : tups)
	{
		for(int i = 0; i < e.size; i++)
		{
			cout << e.tuple[i] << " ";
		}
		cout << endl;
	}
}