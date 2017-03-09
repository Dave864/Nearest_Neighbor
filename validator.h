#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_

#include "classifier.h"
#include <iostream>

class LeaveOneOut
{
	Data *train_data;
	NNeighbor *classifier;
	
public:
	LeaveOneOut(const char *);
	~LeaveOneOut();

	void test(int *);
};

#endif
