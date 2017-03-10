#include <iostream>
#include <string>
#include <stdlib.h>
#include "classifier.h"
#include "validator.h"

int main(int argc, char **argv)
{
	printf("Welcome to Anthony Macpherson's Feature Selection Algorithm.\n");
	printf("Type in the name of the file to test: ");
	std::string file;
	std::getline(std::cin, file);
	Data trial_data(file.c_str());
	int feats[] = {1, 2, 5, 7, -1};
	int exclude[] = {12, -1};
	NNeighbor test(&trial_data, exclude, feats);
	test.PExclude();
	test.PLook();
	double unknown[] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
	int class_t = test.Check(unknown);
	std::cout << "Unkown's class is : " << class_t <<std::endl;
	//printf("Type the number of the algorithm you want to run.\n\n");
	//printf("\t1) Forward Selection\n\t2) Backward Selection\n\t3) Anthony's Special Algorithm\n\n");
	return 0;
}
