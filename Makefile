TARGET = libtweet.so
SHELL = /bin/sh
CC = gcc
CFLAGS = -g -std=c99 -Wall -pedantic -Wextra -c -fPIC 
LFLAGS = -lcurl -lcrypto -lm
OBJECTS = *.o
SOURCE = src/*.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

all: 
	$(CC) $(CFLAGS) $(SOURCE) $(LFLAGS) 
	$(CC) -shared -o $(TARGET) *.o
	ar rcs libtweet.a $(OBJECTS)
	cd tests/ && $(CC) -c *.c && $(CC) 1.o -L../ -ltweet $(LFLAGS) -lgcc

install:
	install $(TARGET) $(BINDIR)
	
clean:
	rm -r *.o
	rm -r *.gch
