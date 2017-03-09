#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <iostream>
#define MAX_FEATURE 64
#define MAX_ROW 2048

struct Data
{
	float d [MAX_ROW][MAX_FEATURE];
	unsigned int row_cnt;
	unsigned int feat_cnt;

	Data(char *data_file)
	{
		feat_cnt = 0;
		row_cnt = 0;
	}

private:
	float My_atof(char *ascii_str)
	{
		return 0.0;
	}

	void Norm()
	{
		return;
	}
};

class NNeighbor
{
};

#endif
