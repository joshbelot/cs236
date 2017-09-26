#include "input_stream.h"
#include "ifstream"
#include "stringstream"
#include "streambuf"

using namespace std;

string read_stream()
{
	ifstream inFile;
	inFile.open("test.txt");

	stringstream strStream;
	strStream << inFile.rdbuf();
	string str = strStream.str();
}