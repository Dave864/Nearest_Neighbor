#include <iostream>
#include <string>
#include <stdlib.h>
#include "classifier.h"

int main(int argc, char **argv)
{
	printf("Welcome to Anthony Macpherson's Feature Selection Algorithm.\n");
	printf("Type in the name of the file to test: ");
	std::string file;
	std::getline(std::cin, file);
	Data trial_data(file.c_str());
	int to_look_1[] = {3, 4, 9, -1};
	int to_exclude_1[] = {1, 4, 6, 10, -1};
	NNeighbor classifier(&trial_data, to_exclude_1, to_look_1);
	classifier.PExclude();
	classifier.PLook();
	std::cout << std::endl;
	int to_exclude_2[] = {2, 4, 6, 7, 8, 10, -1};
	classifier.NewExclude(to_exclude_2);
	classifier.PExclude();
	classifier.PLook();
	std::cout << std::endl;
	int to_look_2[] = {1, 3, -1};
	classifier.NewLook(to_look_2);
	classifier.PExclude();
	classifier.PLook();
	//printf("Type the number of the algorithm you want to run.\n\n");
	//printf("\t1) Forward Selection\n\t2) Backward Selection\n\t3) Anthony's Special Algorithm\n\n");
	return 0;
}
