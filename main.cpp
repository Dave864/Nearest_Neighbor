#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "validator.h"
#include "search.h"

int main(int argc, char **argv)
{
	//Enter the file
	printf("Welcome to Anthony Macpherson's Feature Selection Algorithm.\n");
	printf("Type in the name of the file to test: ");
	std::string file;
	std::getline(std::cin, file);

	//Choose the algorithm
	while(1)
	{
		printf("Type the number of the algorithm you want to run.\n\n");
		printf("\t1) Forward Selection\n\t2) Backward Selection\n\n\t");
		std::string alg;
		std::getline(std::cin, alg);
		if(alg == "1")
		{
			ForSel search_1(file.c_str());
			search_1.Search();
			return 0;
		}
		else if(alg == "2")
		{
			BackElim search_2(file.c_str());
			search_2.Search();
			return 0;
		}
		else
		{
			printf("\nERROR: Invalid input. Input must be a single number with no extra spaces\n");
		}
	}
	return 0;
}
