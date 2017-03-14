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

class SearchAlgorithm
{
protected:
	LeaveOneOut *validator;
	FeatSub *f_subset;
	int f_subset_sz;
	int feat_cnt;
	int *feats_to_use;

	FeatSub best;

	void SearchAction(int*, int) {return;}
	virtual int* SearchHelper() {return NULL;}
public:
	SearchAlgorithm(const char*);
	virtual ~SearchAlgorithm() = 0;

	void Search();
	void PrintSubset();
};

class ForSel : public SearchAlgorithm
{
	/*LeaveOneOut *validator;
	FeatSub *f_subset;
	int f_subset_sz;
	int feat_cnt;
	int *feats_to_use;

	FeatSub best;*/

	void Expand(int*, int);
	int* SearchHelper();

public:
	ForSel(const char* file);// : SearchAlgorithm(file) {};
	~ForSel() {};

	//void Search();
	//void PrintSubset();
};

class BackElim : public SearchAlgorithm
{
	/*LeaveOneOut *validator;
	FeatSub *f_subset;
	int f_subset_sz;
	int feat_cnt;
	int *feats_to_use;

	FeatSub best;*/

	void Contract(int*, int);
	//int *SearchHelper();

public:
	BackElim(const char* file);// : SearchAlgorithm(file) {}
	~BackElim() {};

	//void Search();
	//void PrintSubset();
};

#endif
