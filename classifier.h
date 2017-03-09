#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#define MAX_FEATURE 64
#define MAX_ROW 2048

struct Data
{
	double d [MAX_ROW][MAX_FEATURE];
	unsigned int row_cnt;
	unsigned int feat_cnt;

	Data(const char *);

private:
	double My_atof(char *);
	void Norm();
};

class NNeighbor
{
};

#endif
