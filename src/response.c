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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_tweet(char *key, char *twitter_resp) {
	char *key_pt = strstr(twitter_resp, key);
	if (key_pt == NULL) {
		return NULL;
	}
	
	char *head = strstr(key_pt, ":\"") + 2;
	char *tail = strchr(head, '\"');
	if (tail == NULL) {
		printf("Error in Twitter response. Try again.\n");
		exit(1);
	}
	
	char *buff = malloc((tail-head) * sizeof(char) + 1);
	strncpy(buff, head, tail-head);
	return buff;
}