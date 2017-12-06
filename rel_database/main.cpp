#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "lexer.h"
#include "token.h"
#include "parser.h"

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
	}
	else
	{
		cout << "Could not open specific file.\n";
	}
	return 0;
}