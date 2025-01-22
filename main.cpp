#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "comp_club_description_validator.h"
#include "comp_club.h"
#include "comp_club_parser.h"
#include "comp_club_manger.h"


using namespace std;

static vector<string> read_file_to_vector(const string &path)
{
	vector<string> data;
	ifstream fs;

	fs.open(path);

	if (!fs.is_open())
	{
		throw runtime_error("Eror opening file!");
	}
	else
	{
		string line;
		while (getline(fs, line))
		{
			data.push_back(line);
		}
	}

	return data;
}

int main(int argc, char* argv[])
{
	int exit_code = EXIT_SUCCESS;

	string path;

	if (argc == 2) //User-supplied filename
	{
		path = argv[1];
	}
	else //If the file name was not sent
	{
		path = "computer_club_description.txt";
		cerr << "Path to description was not specified; Using default path: "<< path<< endl << endl;
	}

	try
	{
		vector<string> comp_club_description = read_file_to_vector(path);

		comp_club_description_validator validator(comp_club_description);
		validator.validate();

		comp_club club_data = comp_club_parser::parse(comp_club_description);

		comp_club_manger club(club_data);
		club.manage_day();
	}
	catch (exception& ex)
	{
		cerr << ex.what() << std::endl;
		exit_code = EXIT_FAILURE;
	}
	catch (...)
	{
		cerr << "caught unhandled exception in the main thread" << endl;
		exit_code = EXIT_FAILURE;
	}

	return exit_code;
}