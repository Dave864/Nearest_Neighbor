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

void LeaveOneOut::test(int *feats)//feats must be terminated by a -1
{
	int correct_cnt = 0;
	classifier->NewLook(feats);
	for(int i = 0; (unsigned int)i < train_data->Rows(); i++)
	{
		int to_exclude[] = {i, -1};
		classifier->NewExclude(to_exclude);
		int class_t = classifier->CheckClass((*train_data)[i]);
		if(class_t == (int)(*train_data)[i][0])
		{
			correct_cnt++;
		}
	}
	double accuracy = (double)correct_cnt / (double)train_data->Rows();
	std::cout << "Accuracy is " << accuracy << std::endl;
}
