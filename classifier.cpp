#include "classifier.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

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

double* Data::operator [] (int r)
{
	return d[r];
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
		excluded_inst = new int[ind_cnt];
		memcpy(excluded_inst, exclude, sizeof(int) * ind_cnt);
	}
	else
	{
		excluded_inst = NULL;
	}
}

NNeighbor::~NNeighbor()
{
	delete[] feats_to_look;
	delete[] excluded_inst;
}

//Updates the current indexes of instances to be ignored
void NNeighbor::NewExclude(int *feats)
{
	delete[] excluded_inst;
	int ind_cnt;
	for(ind_cnt = 1; feats[ind_cnt-1] != -1; ind_cnt++);
	excluded_inst = new int[ind_cnt];
	memcpy(excluded_inst, feats, sizeof(int) * ind_cnt);
}

//Updates the current indexes of features to be looked at
void NNeighbor::NewLook(int *feats)
{
	delete[] feats_to_look;
	int ind_cnt;
	for(ind_cnt = 1; feats[ind_cnt-1] != -1; ind_cnt++);
	feats_to_look = new int[ind_cnt];
	memcpy(feats_to_look, feats, sizeof(int) * ind_cnt);
}

//Prints out the current indexes of instances to be ignored
void NNeighbor::PExclude()
{
	std::cout << "Indexes to exclude: ";
	for(int i = 0; excluded_inst[i] != -1; i++)
	{
		std::cout << excluded_inst[i] << " ";
	}
	std::cout << std::endl;
}

//Prints out the current indexes of features to be looked at
void NNeighbor::PLook()
{
	std::cout << "Features to look at: ";
	for(int i = 0; feats_to_look[i] != -1; i++)
	{
		std::cout << feats_to_look[i] << " ";
	}
	std::cout << std::endl;
}

//Prints out the training data
void NNeighbor::PTrain()
{
	for(unsigned int i = 0; i < train_data->Rows(); i++)
	{
		for(unsigned int j = 0; j < train_data->Feats(); j++)
		{
			std::cout << train_data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//Calculates the Euclidean Distance between the instance and an instance at index
double NNeighbor::Dist(double *instance, unsigned int index)
{
	double sum = 0.0;
	for(int i = 0; feats_to_look[i] != -1; i++)
	{
		sum += pow((instance[feats_to_look[i] - 1] - (*train_data)[index][feats_to_look[i]]), 2.0);
	}
	return sqrt(sum);
}

//Checks to see if the index is part of excluded_inst array
bool NNeighbor::IsExcluded(int index)
{
	if(excluded_inst == NULL)
	{
		return false;
	}
	for(int i = 0; excluded_inst[i] != -1; i++)
	{
		if(index == excluded_inst[i])
		{
			return true;
		}
	}
	return false;
}

//Takes in an array of doubles; the first index holds the first feature
int NNeighbor::Check(double *instance)
{
	double min_dist = -1.0;
	double cur_dist, class_pred;
	for(unsigned int i = 0; i < train_data->Rows(); i++)
	{
		if(!IsExcluded(i))
		{
			cur_dist = Dist(instance, i);
			//min_dist is larger than cur_dist
			if((min_dist == -1) || (min_dist > cur_dist))
			{
				min_dist = cur_dist;
				class_pred = (*train_data)[i][0];
			}
		}
	}
	return (int)class_pred;
}
