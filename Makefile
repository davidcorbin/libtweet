SHELL = /bin/sh
TARGET = tweet
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wextra
LFLAGS = -lcurl -lssl -lcrypt -lcrypto
OBJECTS = tweet.c http_methods.c error_desc.c oauth.c xmalloc.c hash.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LFLAGS) $(CFLAGS) $(OBJECTS)

install:
	install $(TARGET) $(BINDIR)