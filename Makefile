CC = g++
OBJS = classifier.o validator.o search.o
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(DEBUG)

select: $(OBJS) main.cpp
	$(CC) $(LFLAGS) $(OBJS) main.cpp -o select

classifier.o: classifier.h classifier.cpp
	$(CC) $(CFLAGS) classifier.cpp

validator.o: validator.h validator.cpp classifier.h
	$(CC) $(CFLAGS) validator.cpp

search.o: search.h search.cpp validator.h
	$(CC) $(CFLAGS) search.cpp

clean:
	\rm *.o select
