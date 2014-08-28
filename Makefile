SHELL = /bin/sh
TARGET = tweet
CC = gcc
CFLAGS = -Wall -lcurl -std=c99 -loauth
OBJECTS = tweet.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJECTS)

install:
	install $(TARGET) $(BINDIR)