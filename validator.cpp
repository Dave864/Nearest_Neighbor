#include "validator.h"
#include "classifier.h"
#include <iostream>

LeaveOutOne::LeaveOutOne(const char *file)
{
	train_data = new Data(file);
	classifier = new NNeighbor(train_data);
}

LeaveOutOne::~LeaveOutOne()
{
	delete train_data;
	delete classifier;
}

void LeaveOutOne::test(int *feats)
{
}
