#include "classifier.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

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
			//std::cout << "Line " << row_cnt << ": " << cur_line << "\n";
			int col_cnt = 0;
			char *tok, *s_ptr;
			char *tok_str = (char *)cur_line.c_str();
			for(tok = strtok_r(tok_str, " \n", &s_ptr); tok != NULL; tok = strtok_r(NULL, " \n", &s_ptr))
			{
				//std::cout << tok << " ";
				My_atof(tok);
				col_cnt++;
			}
			std::cout << std::endl;
			feat_cnt = col_cnt-1;
			row_cnt++;
		}
	}
	in_file.close();
}

double Data::My_atof(char *ascii_str)
{
	char *s_ptr, *tok;
	double value;
	tok = strtok_r(ascii_str, "e+", &s_ptr);
	//std::cout << "Base: " << tok;
	tok = strtok_r(NULL, "e+", &s_ptr);
	//std::cout << ", Exponent: " << tok << std::endl;
	return 0.0;
}

void Data::Norm()
{
}
