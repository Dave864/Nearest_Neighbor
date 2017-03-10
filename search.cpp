#include "search.h"
#include "validator.h"
#include <iostream>

//start of FeatSub functions
FeatSub::FeatSub(int *f, double a)
:accuracy(a)
{
	int f_cnt;
	for(f_cnt = 1; f[f_cnt-1] != -1; f_cnt++);
	feats = new int[f_cnt];
	memcpy(feats, f, sizeof(int) * f_cnt);
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
	f_subset = NULL;
}

ForSel::~ForSel()
{
	delete validator;
}

int* ForSel::search()
{
	return NULL;
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
