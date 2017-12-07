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

void Database::add_to_schemes(Predicate p)
{
	schemes.push_back(p);
}

void Database::add_to_facts(Predicate p)
{
	facts.push_back(p);
}

void Database::add_to_rules(Rule r)
{
	rules.push_back(r);
}

void Database::add_to_queries(Predicate p)
{
	queries.push_back(p);
}

void Database::add_to_domains(string s)
{
	domains.insert(s);
}

void Database::print()
{

}

void Database::create_relations()
{
	for(int i = 0; i < schemes.size(); i++)
	{
		Relation r = Relation(schemes[i].return_name());
		for(int j = 0; j < schemes[i].return_size(); j++)
		{
			r.add_to_schema(schemes[i].return_paramater(j).get_value());
		}
		relations.push_back(r);
	}
}

void Database::populate_relations()
{
	for(int i = 0; i < relations.size(); i++)
	{
		for(int j = 0; j < facts.size(); j++)
		{
			Tuple t = Tuple();
			for(int k = 0; k < facts[j].return_size(); k++)
			{
				t.insert(facts[j].return_parameter(k).get_value());
			}
			relations[i].insert(t);
		}
	}
}

void Database::print_relations()
{
	for(int i = 0; i < relations.size(); i++)
	{
		relations.[i].print();
	}
}

vector<Predicate> Database::return_schemes()
{
	return schemes;
}

vector<Predicate> Database::return_facts()
{
	return facts;
}

vector<Rule> Database::return_rules()
{
	return rules;
}

vector<Predicate> Database::return_queries()
{
	return queries;
}

Relation Database::return_relation(int index)
{

}

Relation Database::get(string n)
{

}

Relation& Database::get2(string n)
{

}

Relation Database::solve_query(Predicate p)
{

}

void Database::solve_queries()
{

}

bool Database::is_found(const vector<Pair>& v, string s)
{

}

int Database::pair_index(const vector<Pair>& v, string s)
{

}

bool Database::is_query_all_strings(Predicate p)
{

}

bool Database::evaluate_rules(Rule r)
{
	Relation accum = Relation("name");
	if(r.return_size() == 1)
	{
		accum = solve_query(r.return_predicate());
	}
	else
	{
		for(int i = 0; i < r.return_size(); i++)
		{
			if(i == 0)
			{
				accum = accum.join(solve_query(r.return_predicate(i)),solve_query(r.return_predicate(i+1)))
			}
			else
			{
				accum = accum.join(accum,solve_query(r.return_predicate))
			}
		}
	}
}

void Database::evaluate_rules()
{
	int count = 0;
	bool repeat = true;
	while(repeat)
	{
		repeat = false;
		for(int 1 = 0; i <rules.size(); i++)
		{
			if(evaluate_rule(rules[i]) == true)
			{
				repeat |= true;
			}
		}
		counter++;
	}
	if(rules.size() == 0)
	{
		count = 0;
	}
	cout << "Schemes populated after " << count << "passes through the Rules." << endl;
}