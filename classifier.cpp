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
		int ind_cnt;
		for(ind_cnt = 1; look[ind_cnt-1] != -1; ind_cnt++);
		feats_to_look = new int[ind_cnt];
		memcpy(feats_to_look, look, sizeof(int) * ind_cnt);
	}
	else
	{
		feats_to_look = new int[train_data->Feats()];
		for(unsigned int i = 0; i < train_data->Feats(); i++)
		{
			feats_to_look[i] = i+1;
		}
	}
	if(exclude != NULL)
	{
		int ind_cnt;
		for(ind_cnt = 1; exclude[ind_cnt-1] != -1; ind_cnt++);
		feats_to_exclude = new int[ind_cnt];
		memcpy(feats_to_exclude, exclude, sizeof(int) * ind_cnt);
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
	delete[] feats_to_exclude;
	int ind_cnt;
	for(ind_cnt = 1; feats[ind_cnt-1] != -1; ind_cnt++);
	feats_to_exclude = new int[ind_cnt];
	memcpy(feats_to_exclude, feats, sizeof(int) * ind_cnt);
}

void NNeighbor::NewLook(int *feats)
{
	delete[] feats_to_look;
	int ind_cnt;
	for(ind_cnt = 1; feats[ind_cnt-1] != -1; ind_cnt++);
	feats_to_look = new int[ind_cnt];
	memcpy(feats_to_look, feats, sizeof(int) * ind_cnt);
}

void NNeighbor::PExclude()
{
	std::cout << "Features to exclude: ";
	for(int i = 0; feats_to_exclude[i] != -1; i++)
	{
		std::cout << feats_to_exclude[i] << " ";
	}
	std::cout << std::endl;
}

void NNeighbor::PLook()
{
	std::cout << "Features to look at: ";
	for(int i = 0; feats_to_look[i] != -1; i++)
	{
		std::cout << feats_to_look[i] << " ";
	}
	std::cout << std::endl;
}

int NNeighbor::Check(double *instance)
{
	return 0;
}
