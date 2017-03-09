#include "classifier.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

//Function definitions for Data object
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

unsigned int Data::Rows()
{
	return row_cnt;
}

unsigned int Data::Feats()
{
	return feat_cnt;
}

void Data::Norm()
{
}
//End of definitions for Data object

//Function definitions for nearest neighbor classifier
NNeighbor::NNeighbor(Data *d, int *exclude, int *look)
{
	train_data = d;
	if(look != NULL)
	{
		int ind_cnt = ((sizeof look) / (sizeof *look));
		std::cout << "Look array size: " << ind_cnt << std::endl;
		feats_to_look = new int[ind_cnt];
		memcpy(feats_to_look, look, ind_cnt);
	}
	else
	{
		std::cout << "Look array size: " << train_data->Feats() << std::endl;
		feats_to_look = new int[train_data->Feats()];
		for(unsigned int i = 0; i < train_data->Feats(); i++)
		{
			feats_to_look[i] = i+1;
		}
	}
	if(exclude != NULL)
	{
		int ind_cnt = ((sizeof exclude) / (sizeof *exclude));
		std::cout << "Exclude array size: " << ind_cnt << std::endl;
		feats_to_exclude = new int[ind_cnt];
		memcpy(feats_to_exclude, exclude, ind_cnt);
	}
	else
	{
		feats_to_exclude = NULL;
	}
}

NNeighbor::~NNeighbor()
{
	delete[] feats_to_look;
	delete[] feats_to_exclude;
}

void NNeighbor::NewExclude(int *feats)
{
}

void NNeighbor::NewLook(int *feats)
{
}

int NNeighbor::Check(double *instance)
{
	return 0;
}
