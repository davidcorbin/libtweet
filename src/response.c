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

char *get_tweet_val(char *key, char *twitter_resp) {
	char *quote_key = calloc( (1 + strlen(key))*sizeof(char) + 1, sizeof(char) );
	strncpy(quote_key, "\"", 1);
	strcat(quote_key, key);

	char *key_pt = strstr(twitter_resp, quote_key);
	if (key_pt == NULL) {
		return NULL;
	}
	
	char *head = strstr(key_pt, ":\"") + 2;
	char *tail = strchr(head, '\"');
	if (tail == NULL) {
		printf("Error in Twitter response json. Try again.\n");
		exit(1);
	}
	
	char *buff = calloc( (tail-head) * sizeof(char) + 1, sizeof(char) );
	memcpy(buff, head, tail-head);
	return buff;
}


void unescape(char *str, char rem) {
	char *src, *dst;
	for (src = dst = str; *src != '\0'; src++) {
		*dst = *src;
		if (*dst != rem) dst++;
	}
	*dst = '\0';
}