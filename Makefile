TARGET = libtweet.so
SHELL = /bin/sh
CC = gcc
CFLAGS = -g -std=c99 -Wall -pedantic -Wextra -c -fPIC 
LFLAGS = -lcurl -lcrypto -lm
OBJECTS = objects/*.o
SOURCE = src/*.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

all: 
	cd objects && $(CC) $(CFLAGS) ../$(SOURCE) $(LFLAGS) 
	$(CC) -shared -o $(TARGET) $(OBJECTS)
	ar rcs libtweet.a $(OBJECTS)
	cd tests/ && $(CC) -c *.c && $(CC) simple.o keys.o -L../ -ltweet $(LFLAGS) -o simple

install:
	install $(TARGET) $(BINDIR)
	
clean:
	rm objects/*.o
	rm libtweet*
	rm tests/*.o 
	rm tests/simple
