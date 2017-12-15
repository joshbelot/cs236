#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "tuple.h"
#include "relation.h"

using namespace std;

void test1(Relation rel)
{
	//rename
	vector<string> attribs = {"ONE", "TWO", "THREE"};
	rel.rename(attribs);
	for(int i = 0; i < rel.schema.size(); i++)
	{
		if(rel.schema[i] != attribs[i])
		{
			cout << "Failure!\n";
			goto next;
		}
	}
	cout << "Success!\n";
	next:;
}

void test2(Relation rel)
{
	//project
	vector<string> attribs = {"One", "Three"};
	Relation rel_proj = rel.project(attribs);
	for(int i = 0; i < rel_proj.schema.size(); i++)
	{
		if(rel_proj.schema[i] != attribs[i])
		{
			cout << "Failure!\n";
			goto next;
		}
	}
	cout << "Success!\n";
	next:;
	for(Tuple t : rel_proj.tups)
	{
		for(int j = 0; j < t.tuple.size(); j++)
		{
			cout << t.tuple[j] << endl;
		}
	}
}

void test3(Relation rel)
{
	//select1
	string attrib = "one";
	string val = "you";
	Relation rel_sel = rel.select1(attrib, val);
}

// void test4()
// {
		//select2
// }

// void test5()
// {
	
// }

// void test6()
// {
	
// }

// void test7()
// {
	
// }

// void test8()
// {
	
// }

// void test9()
// {
	
// }

// void test10()
// {
	
// }


int main(int argc, char** argv)
{
	/*
	//Designate file for token analysis
	ifstream in_file;

	//Open the selected file and put it into a string stream.
	in_file.open(argv[1]);
	if(in_file.is_open())
	{
		string s;
		stringstream ss;
		while(getline(in_file, s))
		{
			if(!in_file.eof())
			{
				ss << s << endl;
			}
			else
			{
				ss << s;
			}
		}

		//Convert stringstream to string
		string resultString = ss.str();

		//Use resultString to create Lexer object
		Lexer lex = Lexer(resultString);

		//Call scan function, which calls the run_all_DFA function.
		//This actually performs the token extraction, as well as
		//pushing the found tokens onto the tokens vector.
		lex.scan();

		Parser pars = Parser(lex.return_vector());
		try
		{
			pars.datalog_parse();
		}
		catch(Token tok1)
		{
			cout << "  " << tok1.toStringToken();
		}

	}
	else
	{
		cout << "Could not open specific file.\n";
	}
	*/
	//For lab 3.1, relations, I need to manually create the parameters for a relation.
	//Then pass them in to a new relation.
	//Then I need to run queries against it.
	//Nah. Just make the stupid db class. Use it simply in 3.1, 
	//	and then actually feed it from the parser for 3.2.

	//1) Make tuples, schema, and names. 
	Tuple A;
	A.insert("'dog'");
	A.insert("'cat'");
	A.insert("'rabbit'");

	Tuple B;
	B.insert("'brother'");
	B.insert("'sister'");
	B.insert("'uncle'");

	Tuple C;
	C.insert("'squid'");
	C.insert("'shark'");
	C.insert("'stingray'");

	Tuple D;
	D.insert("'sandal'");
	D.insert("'boot'");
	D.insert("'galosh'");

	Tuple E;
	E.insert("'mom'");
	E.insert("'dad'");

	Tuple F;
	F.insert("'Tom'");
	F.insert("'Jerry'");

	Tuple G;
	G.insert("'you'");
	G.insert("'me'");

	Tuple H;
	H.insert("'this'");
	H.insert("'that'");

	set<Tuple> t3;
	t3.insert(A);
	t3.insert(B);
	t3.insert(C);
	t3.insert(D);

	set<Tuple> t2;
	t2.insert(E);
	t2.insert(F);
	t2.insert(G);
	t2.insert(H);

	vector<string> s3 = {"One", "Two", "Three"};
	vector<string> s2 = {"one", "two"};

	string name1 = "name1";
	string name2 = "name2";

	//2) Initialize relations.
	Relation rel1 = Relation(name1, s3, t3);
	Relation rel2 = Relation(name2, s2, t2);

	//3) Make 10 test cases.
	test1(rel1);
	test2(rel1);
	test3(rel2);
	//test4(rel2);

	return 0;
}