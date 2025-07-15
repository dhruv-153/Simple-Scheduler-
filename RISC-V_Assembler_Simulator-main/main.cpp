#include <bits/stdc++.h>
#include <fstream>
#include "func_file.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		cout<< "Wrong Format, please follow the following format:" <<endl;
		cout<< "./main <input_file_name> <output_file_name>" <<endl;
		exit(0);
	}
	string input_file_name = argv[1];
	string output_file_name = argv[2];

	//Assembler *a = new Assembler();
	
	//a->store_labels(input_file_name);
	//a->read_and_write(input_file_name, output_file_name);
	//a->check_errors(output_file_name);

	//delete a;

	simulator *b = new simulator();

	b->read(input_file_name);
	b->write(output_file_name);

	delete b;

	return 0;
}


