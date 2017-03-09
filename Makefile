CC = g++
OBJS = classifier.o
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(DEBUG)

select: $(OBJS) main.cpp
	$(CC) $(LFLAGS) $(OBJS) main.cpp -o select

classifier.o: classifier.h classifier.cpp
	$(CC) $(CFLAGS) classifier.cpp

clean:
	\rm *.o select
