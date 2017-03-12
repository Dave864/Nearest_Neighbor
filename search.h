#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <iostream>
#include "validator.h"

struct FeatSub
{
	int *feats;
	double accuracy;

	FeatSub(int* f = NULL, double a = 0.0);
	~FeatSub();

	void operator = (int *);
	void Print();
};

class ForSel
{
	LeaveOneOut *validator;
	FeatSub *f_subset;
	int f_subset_sz;
	int feat_cnt;
	int *feats_to_use;

	FeatSub best;

	void Expand(int*, int);
	int* SearchHelper();

public:
	ForSel(const char*);
	~ForSel();

	void Search();
	void PrintSubset();
};

class BackElim
{
	LeaveOneOut *validator;
	FeatSub *f_subset;
	int feat_cnt;

public:
	BackElim(const char*);
	~BackElim();

	int* search();
};

#endif
