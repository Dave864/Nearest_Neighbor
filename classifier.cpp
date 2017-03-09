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
			int col_cnt = 0;
			char *tok, *s_ptr;
			char *tok_str = (char *)cur_line.c_str();
			for(tok = strtok_r(tok_str, " \n", &s_ptr); tok != NULL; tok = strtok_r(NULL, " \n", &s_ptr))
			{
				d[row_cnt][col_cnt] = atof(tok);
				col_cnt++;
			}
			feat_cnt = col_cnt-1;
			row_cnt++;
		}
	}
	in_file.close();
}

void Data::Norm()
{
}
