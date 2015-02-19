SHELL = /bin/sh
TARGET = tweet
CC = gcc
CFLAGS = -g -std=c99 -Wall -pedantic -Wextra
LFLAGS = -lcurl -lcrypto -lm
OBJECTS = src/*.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET) 

install:
	install $(TARGET) $(BINDIR)
	
clean:
	rm *.o
	rm *.gch