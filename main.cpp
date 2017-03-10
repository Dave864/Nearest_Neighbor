#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "search.h"

int main(int argc, char **argv)
{
	printf("Welcome to Anthony Macpherson's Feature Selection Algorithm.\n");
	printf("Type in the name of the file to test: ");
	std::string file;
	std::getline(std::cin, file);
	printf("Running Forward Selection\n");
	ForSel search_1(file.c_str());
	//search_1.Search(); 
	//printf("Type the number of the algorithm you want to run.\n\n");
	//printf("\t1) Forward Selection\n\t2) Backward Selection\n\t3) Anthony's Special Algorithm\n\n");
	return 0;
}
