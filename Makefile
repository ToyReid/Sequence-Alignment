# CS360 Class Manager
# August 29, 2005
CC = g++
#INCLUDES = .
CFLAGS = -g -Wall -std=c++11 #-I$(INCLUDES)
EXECUTABLES = driver

all: $(EXECUTABLES)

driver: main.o align.o globalign.o localign.o egfalign.o
	$(CC) $(CFLAGS) -o driver main.o align.o globalign.o localign.o egfalign.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

align.o: align.cpp
	$(CC) $(CFLAGS) -c align.cpp

globalign.o: globalign.cpp
	$(CC) $(CFLAGS) -c globalign.cpp

localign.o: localign.cpp
	$(CC) $(CFLAGS) -c localign.cpp

egfalign.o: egfalign.cpp
	$(CC) $(CFLAGS) -c egfalign.cpp

clean:
	rm $(EXECUTABLES) *.o