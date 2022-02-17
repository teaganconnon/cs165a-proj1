CC=g++
CFLAGS= -g -std=c++11 -Wall

default: main

main: main.o NaiveBayesClassifier.o preprocessing.o  probability.o
	$(CC) $(CFLAGS) -o main main.o NaiveBayesClassifier.o preprocessing.o  probability.o

main.o: main.cpp preprocessing.h NaiveBayesClassifier.h probability.h
	$(CC) $(CFLAGS) -c main.cpp

NaiveBayesClassifier.o: NaiveBayesClassifier.h probability.h preprocessing.h
#	$(CC) $(CFLAGS) -c NaiveBayesClassifier.cpp

preprocessing.o: preprocessing.h
#	$(CC) $(CFLAGS) -c preprocessing.cpp

probability.o: probability.h
#	$(CC) $(CFLAGS) -c probability.cpp

clean:
	$(RM) main *.o *~