rest Neighbor
An implementation of the nearest neighbor classification algorithm.

The nearest neighbor classification algorithm is used inside two different searches.
- Forward Selection
- Backward Elimination

Each search determines the feature subset with the best possible accuracy for correctly classifying a new data point given a set of training data.

### Data file format
A data file for this program is a list of floating point numbers seperated by whitespace. The format of the number is the ASCII text, IEE standard for 8 place floating point numbers.

Each line in the data file is a data point. The first number on each line is the class that the data point belongs to. The following numbers are the values of each feature in the data point. All data points in the file have the same number of features

The following is a datafile example with 5 points of data, each with 3 features.

	1.0000000e+000  2.0012309e+010  5.7291025e+000  1.2088700e-001
	1.0000000e+000  4.9906351e-201  4.0000021e+100  4.0020259e-010 
	2.0000000e+000  2.0009350e+012 3.9820716e+001  4.0012034e-003 
	1.0000000e+000  5.0099921e+200  7.1210002e+031  2.3061002e+005
	2.0000000e+000  3.0000012e+000  6.1112003e+001  1.9827014e-092

A file can have at most 1024 data points. Each data point can have up to 40 features. Each data point can be one of two classes, 1 or 2.

### How to Compile
It is recommended that the makfile is used.
To use the makefile you must first download the following files:
- Makefile
- main.cpp
- classifier.h
- classifier.cpp
- validator.h
- validator.cpp
- search.h
- search.cpp

Once the files are downloaded simply type in the "make" command into the terminal.

	make

The exucutable is called select.

To remove the executable and object files type in the following command.

	make clean

### How to Run 
1) Compile the program
2) Run the executable with the following command

		./select
3) The following prompt will appear

		Welcome to Anthony Macpherson's Feature Selection Algorithm.
		Type in the name of the file to test: <file_path>

	Enter the path to the file you wish to test. The <file_path> label is where the name of the file path you enter will appear in the prompt.
4) The program will prompt you to pick an algorithm

		Type in the number of the algorithm you want to run.
		1) Forward Selection
		2) Backward Elimination

			<choice>

	Enter the number of the algorithm you wish to run.The number you enter will appear where the <choice> label is located. If an invalid number is entered, the following message displays

		ERROR: Invalid input. Input must be a single number with no extra spaces

	You will then be prompted again to pick an algorithm
5) The program executes the chosen algorithm. The program displays the steps it takes as it evaluates the data.

		This dataset has <feat_num> features (not including the class attribute), with <data_count> instances.
		Normalizing data, please wait...

		Running <algorithm>

		Beginning Search.

			Using feature(s) {<features>} accuracy is <accuracy>
		...

		<The following is repeated>>>>>>>>>>>>>>>>>>>
		Feature set {<features>} was best, accuracy is <accuracy>

			Using feature(s) {<features>} accuracy is <accuracy>
		<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	Once the algorithm has finished it will display the results

		Finished search!! The best feature subset is {<features>}, which has an accuracy of <accuracy> 

	The following is a description of the labels in the above code segments
	- <algorithm>: The name of the algorithm you chose
	- <features>: a list of comma seperated numbers, indicating the features being looked at
	-- Example: 1, 2, 3, 5, 8
	- <accuracy>: a decimal number followed by a percent sign, indicating the accuracy value
	-- Example: 0.56%

### Known Bugs and Errors
The program does not do error checking to see if the test file is a valid file. 

The program cannot handle data files that differ from the format listed in the section "Data file format".

This program has only been tested on a Linux operating system. The program may not work on other systems.
