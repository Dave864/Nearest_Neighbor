#include "validator.h"
#include "classifier.h"
#include <iostream>

LeaveOneOut::LeaveOneOut(const char *file)
{
	train_data = new Data(file);
	classifier = new NNeighbor(train_data);
}

LeaveOneOut::~LeaveOneOut()
{
	delete train_data;
	delete classifier;
}

void LeaveOneOut::test(int *feats)
{
}
