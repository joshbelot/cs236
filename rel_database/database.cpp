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
	cout << "Success!\n";
	cout << "Schemes(" << schemes.size() << "):\n";
	for(int a = 0; a < schemes/size(); a++)
	{
		cout << " " << schemes[a].toString() << endl;
	}
	cout << "Facts(" << facts.size() << "):\n";
	for(int b = 0; b < facts.size(); b++)
	{
		cout << " " << facts[b].toString() << "." << endl;
	}
	cout << "Rules(" << rules.size() << "):\n";
	for(int c = 0; c < rules.size(); c++)
	{
		cout << " " << rules[c].toString() << endl;
	}
	cout << "Queries(" << queries.size() << "):\n";
	for(int d = 0; d < queries.size(); d++)
	{
		cout << " " << queries[d].toString() << "?" << endl;
	}
	cout << "Domain(" << domain.size() << "):\n";
	for(auto e : domain)
	{
		cout << " " << e << endl;
	}
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
	return relations[index];
}

Relation Database::get(string n)
{
	for(int i =0; i < relations.size(); i++)
	{
		if(relations[i].name == n)
		{
			return relations[i];
		}
	}
	retun Relation("");
}

Relation& Database::get2(string n)
{
	for(int i = 0; i < relations.size(); i++)
	{
		if(relations[i].name == n)
		{
			return relations[i];
		}
	}
}

Relation Database::solve_query(Predicate p)
{
	Relation r = get(p.return_name());
	vector<string> rename_to;
	vector<string project_to;
	vector<Pair> pairs;
	for(int i = 0; i < p.return_size(); i++)
	{
		if(p.return_parameter(i).get_type() == STRING)
		{
			rename_to.push_back(r.schema[i]);
			r = r.select1(r.schema[i], p.return_parameter(i).get_value());
		}
		if(p.return_parameter(i).get_type() == ID)
		{
			if(!is_found(pairs, p.return_parameter(i).get_value()))
			{
				rename_to.push_back(p.return_parameter(i).get_value());
				project_to.push_back(p.return_parameter(i).get_value());
				pairs.push_back(Pair(p.return_parameter(i).get_value(), i));
			}
			else
			{
				rename_to.push_back(r.schema[i]);
				r = r.select2(r.schema[i], r.schema[pair_index(pairs, p.return_parameter(i).get_value())]);
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
	for(int i = 0; i < queries.size(); i++)
	{
		r = solve_query(queries[i]);
		cout << queries[i].toString() << "? ";
		if(is_query_all_strings(queries[i]))
		{
			goto next;
		}
		else
		{
			cout << "No" << endl;
			goto next;
		}
		for(Tuple t : r.tuples)
		{
			cout << " ";
			for(int j = 0; j < r.schema.size(); j++)
			{
				if(j == (r.schema.size() - 1))
				{
					cout << r.schema[j] << "=" << t.tuple[j] << endl;
				}
				else
				{
					cout << r.schema[j] << "=" << t.tuple[j] << ", ";
				}
			}
		}
		next:;
	}
}

bool Database::is_found(const vector<Pair>& v, string s)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i].id == s)
		{
			return true;
		}
	}
	return false;
}

int Database::pair_index(const vector<Pair>& v, string s)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i].id == s)
		{
			return v[i].index;
		}
	}
	return -1;
}

bool Database::is_query_all_strings(Predicate p)
{
	for(int i = 0; i < p.return_size(); i++)
	{
		if(p.return_parameter(i).get_type() == ID)
		{
			return false;
		}
	}
	return true;
}

bool Database::evaluate_rule(Rule r)
{
	Relation accumulate = Relation("name");
	if(r.return_size() == 1)
	{
		accumulate = solve_query(r.return_predicate(0));
	}
	else
	{
		for(unsigned int i = 0; i < r.return_size(); i++)
		{
			if(i == 0)
			{
				accumulate = accumulate.join(solve_query(r.return_predicate(i)),solve_query(r.return_predicate(i+1)));
				i = 1;
			}
			else
			{
				accumulate = accumulate.join(accumulate,solve_query(r.return_predicate(i)));
			}
		}
	}
	accumulate = accumulate.project(r.return_head().return_parameters_as_strings());
	unsigned int check = get(r.return_head().return_name()).tuples.size();
	for(Tuple t : accumulate.tuples)
	{
		get2(r.return_head().return_name()).insert(t);
	}
	if(check == get(r.return_head().return_name()).tuples.size())
	{
		return false;
	}
	else
	{
		return true;
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