SHELL = /bin/sh
TARGET = tweet
CC = gcc
# -Wall -Wextra
CFLAGS = -g -lcurl -std=c99
OBJECTS = tweet.c http_methods.c error_desc.c oauth.c xmalloc.c hash.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJECTS)

install:
	install $(TARGET) $(BINDIR)