#include "database.h"

Database::Database()
{
	vector<Predicate> schems;
	vector<Predicate> facts;
	vector<Rule> rules;
	vector<Predicate> queries;
	set<string> domain;
	vector<Relation> relations;
}

void Database::add_to_schema(Predicate p)
{
	
}

void Database::add_to_facts(Predicate p)
{
	
}

void Database::add_to_queries(Predicate p)
{
	
}

void Database::add_to_domain(string s)
{
	
}

Relation Database::get(sting n)
{
	for(int i =0; i < relations.size(); i++)
	{
		if(relations[i].name == n)
		{
			return relations[i];
		}
	}
	return(Relation(""));
}

Relation Database::solve_query(Predicate p)
{
	Relation r = get(p.return_name());
	vector<string> rename_to;
	vector<string> project_to;
	vector<Pair> pairs;

	//Work through each parameter of the query
	for(int i = 0; i < p.return_size(); i++)
	{
		if(p.return_param(i).get_type() == STRING)
		{
			rename_to.push_back(r.schema[i]);
		}
		if(p.return_param(i).get_type() == ID)
		{
			if(!is_found(pairs, p.return_param(i).get_value()))
			{
				rename_to.push_back(p.return_param(i).get_value());
				project_to.push_back(p.return_param(i).get_value());
				pairs.push_back(Pair(p.return_param(i).get_value(), i));
			}
			else
			{
				rename_to.push_back(r.schema[i]);
				r = r.select2(r.schema[i], r.schema[pair_index(pairs, p.return_param(i).get_value())]);
			}
		}
	}
	r.rename(rename_to);
	if(project_to.size() > 0)
	{
		r = r.project(project_to);
	}
	return r;
}

void Database::solve_queries()
{
	Relation r = Relation("new");
	for(unsigned int i = 0; i < queries.size(); i++)
	{
		r = solve_query(queries[i]);
		cout << queries[i].toString() << "? ";
		if(r.tuples.size() > 0)
		{
			cout << "Yes(" << r.tuples.size() << ")" << endl;
			if(is_query_all_strings(queries[i]))
			{
				goto next;
			}
		}
		else
		{
			cout << "No" << endl;
		  	goto next;
		}
		for(Tuple t : r.tups)
		{
			cout << " ";
			for(int j = 0; j < r.schema.size(); j++;)
			{
				if(j == (r.schema.size() - 1))
				{
					cout << r.schema[j] << "=" << .tuple[j] << endl;
				}
				else
				{
					cout << r.schema[j] << "=" << .tuple[j] << ", ";
				}
			}
		}
		next:;
	}
}

void Database::print()
{

}