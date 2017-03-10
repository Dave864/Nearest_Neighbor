#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <iostream>
#include "validator.h"

struct FeatSub
{
	int *feats;
	double accuracy;

	FeatSub(int*, double a = 0.0);
	~FeatSub();
};

class ForSel
{
	LeaveOneOut *validator;
	FeatSub *f_subset;
	int feat_cnt;

public:
	ForSel(const char*);
	~ForSel();

	int* search();
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
