#include "input_stream.h"
#include <iostream>
#include <fstream>

using namespace std;

string read_stream()
{
	ifstream file("test.txt");
	string temp;
	string result;
	while(getline(file, temp)){
		result += temp;
		result.push_back('\n');
	}
	return result;
}