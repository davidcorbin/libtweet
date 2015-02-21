/*
 *
 * Copyright (c) 2015 David Corbin.
 *
 * This library is free software; 
 * you can redistribute it and/or modify
 * it under the terms of the MIT license. 
 * See COPYING for details.
 *
 */

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#include <unistd.h>
#include <pwd.h>

char *getKey(char *filename) {
	char *homedir = getpwuid(getuid())->pw_dir;
	char *keydir = "/.tweet/";
	char *tweetdir = malloc((strlen(homedir)*sizeof(char)) + (strlen(keydir)*sizeof(char)) + (strlen(filename)*sizeof(char)) + 1);
	strcpy(tweetdir, homedir);
	strcat(tweetdir, keydir);
	strcat(tweetdir, filename);
	
	FILE *fp = fopen(tweetdir, "a+");	
	if (fp == NULL) {
	 	perror("Error");
	}
	char *buff = malloc(50);
    fscanf(fp, "%s", buff);
    fclose(fp);

	return buff;
}


/*** Functions for setting Twitter credentials in file ***/
void setConsumerKey(char *key) {
	FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/consumerkey"), "w");
	if (fp == NULL) {
		perror("Write Error:");
	}
	else {
		fputs(key, fp);
		fclose(fp);
	}
}

void setConsumerSecret(char *key) {
        FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/consumersecret"), "w");
        if (fp == NULL) {
                perror("Write Error:");
        }
        else {
                fputs(key, fp);
                fclose(fp);
        }
}

void setUserToken(char *key) {
        FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/usertoken"), "w");
	if (fp == NULL) {
                perror("Write Error:");
        }
        else {
                fputs(key, fp);
                fclose(fp);
        }
}

void setUserSecret(char *key) {
        FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/usersecret"), "w");
	if (fp == NULL) {
                perror("Write Error:");
	}
        else {
                fputs(key, fp);
                fclose(fp);
        }
}
