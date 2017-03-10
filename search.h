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
};

class ForSel
{
	LeaveOneOut *validator;
	FeatSub *f_subset;
	int feat_cnt;
	int *feats_to_use;

	double best_acc;
	int* best_set;

	void Expand(int*, int);

public:
	ForSel(const char*);
	~ForSel();

	int* Search();
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
