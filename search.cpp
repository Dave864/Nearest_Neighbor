#include "search.h"
#include "validator.h"
#include <iostream>

//start of FeatSub functions
FeatSub::FeatSub(int *f, double a)
:accuracy(a)
{
	if(f != NULL)
	{
		int f_cnt;
		for(f_cnt = 1; f[f_cnt-1] != -1; f_cnt++);
		feats = new int[f_cnt];
		memcpy(feats, f, sizeof(int) * f_cnt);
	}
}

FeatSub::~FeatSub()
{
	delete[] feats;
}
//end of FeatSub functions

//start of ForSel functions
ForSel::ForSel(const char *file)
{
	validator = new LeaveOneOut(file);
	feat_cnt = validator->FeatCnt();

	//Create an array of features that can be used
	feats_to_use = new int[feat_cnt];
	for(int i = 0; i < feat_cnt; i++)
	{
		feats_to_use[i] = i+1;
	}
	
	//Initialize the result and subset containers
	best_acc = 0.0;
	f_subset = NULL;
	best_set = NULL;
}

ForSel::~ForSel()
{
	delete validator;
	delete[] feats_to_use;
}

//Expand the feature set
void ForSel::Expand(int *cur_best, int subset_sz)
{
	f_subset = new FeatSub[feat_cnt - subset_sz];
	int subset_ind = 0;
	for(int i = 0; i < feat_cnt; i++)
	{
		if(feats_to_use[i] >= 0)
		{
			int *new_set = new int[subset_sz + 2];
			memcpy(new_set, cur_best, sizeof(int) * subset_sz);
			//Add the new feature to the existing set
			new_set[subset_sz] = feats_to_use[i];
			//Append -1 to the end of the set
			new_set[subset_sz + 1] = -1;
			f_subset[subset_ind].feats = new_set;
			subset_ind++;
		}
	}
}

int* ForSel::Search()
{
	double cur_acc = 0.0;
	int *cur_set = NULL;

	for(int i = 0; i <= feat_cnt; i++)
	{
		//Get best accuracy of current subset
		if(f_subset != NULL)
		{
			cur_acc = -1.0;
			cur_set = NULL;
			for(int j = 0; j <= (feat_cnt - i); j++)
			{
				double f_acc;
				if((f_acc = validator->Test(f_subset[j].feats)) > cur_acc)
				{
					cur_acc = f_acc;
					cur_set = f_subset[j].feats;
				}
			}
			//Update best_acc and best_set
			if(cur_acc > best_acc)
			{
				best_acc = cur_acc;
				best_set = new int[i + 1];
				memcpy(best_set, cur_set, sizeof(int) * (i + 1));
			}
			delete[] f_subset;
			//Update feats_to_use
			for(int t = 0; t < (i + 1); t++)
			{
				feats_to_use[cur_set[t]] = -1;
			}
		}
		Expand(cur_set, i);
	}
	return best_set;
}
//end of ForSel functions

//start of BackElim functions
BackElim::BackElim(const char *file)
{
	validator = new LeaveOneOut(file);
	feat_cnt = validator->FeatCnt();
	f_subset = NULL;
}

BackElim::~BackElim()
{
	delete validator;
}

int* BackElim::search()
{
	return NULL;
}
