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
	else
	{
		feats = f;
	}
}

FeatSub::FeatSub(const FeatSub &original)
{
	if(original.feats != NULL)
	{
		int f_cnt;
		for(f_cnt = 1; original.feats[f_cnt-1] != -1; f_cnt++);
		feats = new int[f_cnt];
		memcpy(feats, original.feats, sizeof(int) * f_cnt);
	}
	else
	{	
		feats = NULL;
	}
	accuracy = original.accuracy;
}

FeatSub::~FeatSub()
{
	delete[] feats;
}

void FeatSub::operator = (int *new_feats)
{
	int *feats_tmp = feats;
	if(new_feats != NULL)
	{
		int f_cnt;
		for(f_cnt = 1; new_feats[f_cnt-1] != -1; f_cnt++);
		feats = new int[f_cnt];
		memcpy(feats, new_feats, sizeof(int) * f_cnt);
	}
	else
	{
		feats = new_feats;
	}
	delete[] feats_tmp;
}

void FeatSub::operator = (FeatSub original)
{
	(*this) = original.feats;
	accuracy = original.accuracy;
}

void FeatSub::Print()
{
	std::cout << "{";
	if(feats != NULL)
	{
		for(int i = 0; feats[i] != -1; i++)
		{
			if(i > 0)
			{
				std::cout <<  ", ";
			}
			std::cout << feats[i];
		}
	}
	std::cout << "}";
}
//end of FeatSub functions

//start of SearchAlgortihm base class
SearchAlgorithm::SearchAlgorithm(const char * file)
{
	validator = new LeaveOneOut(file);
	feat_cnt = validator->FeatCnt();
	
	//Initialize the result and subset containers
	f_subset = NULL;
	f_subset_sz = 0;
	best.accuracy = 0.0;
	best = NULL;
}

SearchAlgorithm::~SearchAlgorithm()
{
	delete validator;
	delete[] f_subset;
	delete[] feats_to_use;
}

void SearchAlgorithm::Search()
{
	std::cout << "Beginning Search.\n\n";
	SearchHelper();
	std::cout << "Finished search!! The best feature subset is ";
	best.Print();
	std::cout << ", which has an accuracy of ";
	std::cout << best.accuracy << "%\n";
}

void SearchAlgorithm::PrintSubset()
{
	std::cout << "{";
	for(int i = 0; i < f_subset_sz; i++)
	{
		if(i > 0)
		{
			std::cout << ", ";
		}
		f_subset[i].Print();
	}
	std::cout << "}\n";
}
//end of SearchAlgorithm base class

//start of ForSel functions
ForSel::ForSel(const char *file):SearchAlgorithm(file)
{
	//Create an array of features that can be used
	feats_to_use = new int[feat_cnt];
	for(int i = 0; i < feat_cnt; i++)
	{
		feats_to_use[i] = i+1;
	}

	//Prompt
	std::cout << "\nRunning Forward Selection\n\n";
}

//Expand the feature set
void ForSel::Expand(int *cur_best, int subset_sz)
{
	f_subset = new FeatSub[feat_cnt - subset_sz];
	f_subset_sz = feat_cnt - subset_sz;
	int subset_ind = 0;
	for(int i = 0; i < feat_cnt; i++)
	{
		if(feats_to_use[i] >= 0)
		{
			f_subset[subset_ind].feats = new int[subset_sz + 2];
			memcpy(f_subset[subset_ind].feats, cur_best, sizeof(int) * subset_sz);
			//Add the new feature to the existing set
			f_subset[subset_ind].feats[subset_sz] = feats_to_use[i];
			//Append -1 to the end of the set
			f_subset[subset_ind].feats[subset_sz + 1] = -1;
			subset_ind++;
		}
	}
}

//Runs the actual search
int* ForSel::SearchHelper()
{
	FeatSub cur;

	for(int i = 0; i <= feat_cnt; i++)
	{
		//Get best accuracy of current subset
		if(f_subset != NULL)
		{
			cur.accuracy = -1.0;
			for(int j = 0; j <= (feat_cnt - i); j++)
			{
				double f_acc;
				if((f_acc = validator->Test(f_subset[j].feats)) > cur.accuracy)
				{
					cur.accuracy = f_acc;
					cur = f_subset[j].feats;
				}
			}
			//Update best_acc and best_set
			if(cur.accuracy > best.accuracy)
			{
				best.accuracy = cur.accuracy;
				best = cur.feats;
				std::cout << std::endl;
			}
			//Print out message saying that current best feature set is not the best set
			else
			{
				std::cout << "\n(Warning, Accuracy has decreased!";
				std::cout << " Continuing search in case of local maxima)\n";
			}
			//Print out the current best feature set
			std::cout << "Feature set ";
			cur.Print();
			std::cout << " was best, accuracy is " << cur.accuracy << "%\n\n";
			delete[] f_subset;
			//Update feats_to_use
			for(int t = 0; cur.feats[t] != -1; t++)
			{
				feats_to_use[cur.feats[t] - 1] = -1;
			}
		}
		Expand(cur.feats, i);
	}
	return best.feats;
}
//end of ForSel functions

//start of BackElim functions
BackElim::BackElim(const char *file):SearchAlgorithm(file)
{
	//Create an array of features that can be used
	feats_to_use = new int[feat_cnt + 1];
	for(int i = 0; i < feat_cnt; i++)
	{
		feats_to_use[i] = i+1;
	}
	feats_to_use[feat_cnt] = -1;

	//Create the initial feature subset
	f_subset = new FeatSub[1];
	f_subset[0] = feats_to_use;
	f_subset_sz = feat_cnt;

	//Prompt
	std::cout << "\nRunning Backward Elimination\n\n";
}

//Expand the feature set
void BackElim::Expand(int *cur_best, int subset_sz)
{
	f_subset = new FeatSub[feat_cnt - subset_sz];
	f_subset_sz = feat_cnt - subset_sz;

	for(int i = 0; i < f_subset_sz; i++)
	{
		f_subset[i].feats = new int[f_subset_sz];
		//Remove one feature from the cur_best
		int ind = 0;
		for(int j = 0; j <= f_subset_sz; j++)
		{
			if(cur_best[j] != cur_best[i] || cur_best[j] == -1)
			{
				f_subset[i].feats[ind] = cur_best[j];
				ind++;
			}
		}
	}
}

//Runs the actual search
int* BackElim::SearchHelper()
{
	//Initialize best
	best.accuracy = validator->Test(f_subset[0].feats);
	best = f_subset[0].feats;

	FeatSub cur = best;

	std::cout << std::endl;

	for(int i = 0; i <= feat_cnt; i++)
	{
		//Get best accuracy of current subset
		if(i > 0)
		{
			cur.accuracy = -1.0;
			for(int j = 0; j <= (feat_cnt - i); j++)
			{
				double f_acc;
				if((f_acc = validator->Test(f_subset[j].feats)) > cur.accuracy)
				{
					cur.accuracy = f_acc;
					cur = f_subset[j].feats;
				}
			}
			//Update best_acc and best_set
			if(cur.accuracy > best.accuracy)
			{
				best.accuracy = cur.accuracy;
				best = cur.feats;
				std::cout << std::endl;
			}
			//Print out message saying that current best feature set is not the best set
			else
			{
				std::cout << "\n(Warning, Accuracy has decreased!";
				std::cout << " Continuing search in case of local maxima)\n";
			}
		}
		//Print out the current best feature set
		std::cout << "Feature set ";
		cur.Print();
		std::cout << " was best, accuracy is " << cur.accuracy << "%\n\n";
		delete[] f_subset;
		Expand(cur.feats, i);
	}
	return best.feats;
}
