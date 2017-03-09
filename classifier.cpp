#include "classifier.h"
#include <iostream>
#include <fstream>
#include <string>

Data::Data(const char *data_file)
{
	feat_cnt = 0;
	row_cnt = 0;
	std::string cur_line;
	std::ifstream in_file;
	in_file.open(data_file, std::ifstream::in);
	while(in_file.good())
	{
		std::getline(in_file, cur_line);
		if(cur_line != "")
		{
			std::cout << "Line " << row_cnt << ": " << cur_line << "\n";
			row_cnt++;
		}
	}
	in_file.close();
}

double Data::My_atof(char *ascii_str)
{
	return 0.0;
}

void Data::Norm()
{
}
