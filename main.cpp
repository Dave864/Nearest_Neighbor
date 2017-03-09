#include <iostream>
#include "classifier.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		std::cout << "Please enter a file\n";
		return 0;
	}
	Data test(argv[1]);
	return 0;
}
