SHELL = /bin/sh
TARGET = tweet
CC = gcc
CFLAGS = -Wall -Wextra -g -lcurl -std=c99 -loauth -ljson
OBJECTS = tweet.c http_methods.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJECTS)

install:
	install $(TARGET) $(BINDIR)