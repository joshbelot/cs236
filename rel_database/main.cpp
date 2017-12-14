#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "database.h"

using namespace std;

/*
Questions for the TAs
1) Should the final domain end with a new line?
*/

int main(int argc, char** argv)
{
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
		//For lab 3.1, relations, I need to manually create the parameters for a relation.
		//Then pass them in to a new relation.
		//Then I need to run queries against it.
		//Nah. Just make the stupid db class. Use it simply in 3.1, 
		//	and then actually feed it from the parser for 3.2.
	}
	else
	{
		cout << "Could not open specific file.\n";
	}
	return 0;
}