SHELL = /bin/sh
TARGET = tweet
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wextra
LFLAGS = -lcurl -lcrypto -lm
OBJECTS = tweet.c http_methods.c error_desc.c oauth.c xmalloc.c hash.c
PREFIXDIR = $(DESTDIR)/usr
BINDIR = $(PREFIXDIR)/bin

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET) 

install:
	install $(TARGET) $(BINDIR)
	
clean:
	rm *.o
	rm *.gch