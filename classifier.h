#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <iostream>
#define MAX_FEATURE 64
#define MAX_ROW 2048

struct Data
{
	double d [MAX_ROW][MAX_FEATURE];
	Data(const char *);

	unsigned int Rows();
	unsigned int Feats();
private:
	unsigned int row_cnt;
	unsigned int feat_cnt;

	void Norm();
};

class NNeighbor
{
	int *feats_to_look;
	int *feats_to_exclude;
	Data *train_data;

	double Dist();
public:
	NNeighbor(Data *, int *exclude = NULL, int *look = NULL);
	~NNeighbor();

	void NewExclude(int *);
	void NewLook(int *);

	int Check(double *);
};

#endif
