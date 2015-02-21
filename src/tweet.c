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

#include "tweet.h"
#include "http.h"
#include "oauth.h"

struct auth {
	char *consumer_key;
	char *consumer_secret;
	char *access_token;
	char *access_secret;
};

TWITTER_AUTH *twitter_auth_init(char *consumer_key, char *consumer_secret, char *access_token , char *access_secret) {

	// Try to allocate struct
	TWITTER_AUTH *auth = malloc(sizeof(TWITTER_AUTH));
	if (auth == NULL) {
		printf("Failed to allocate auth\n");
		exit(-1);
	}

	// Try to allocate for consumer key and set	
	auth->consumer_key = malloc(strlen(consumer_key) * sizeof(char) + 1);
	if (auth->consumer_key == NULL) {
		free(auth);
		printf("Failed to allocate consumer key\n");
		exit(-1);
	}
	
	// Try to allocate for consumer secret and set	
	auth->consumer_secret = malloc(strlen(consumer_secret) * sizeof(char) + 1);
	if (auth->consumer_secret == NULL) {
		free(auth);
		printf("Failed to allocate consumer secret\n");
		exit(-1);
	}
	
	// Try to allocate for consumer key and set	
	auth->access_token = malloc(strlen(access_token) * sizeof(char) + 1);
	if (auth->access_token == NULL) {
		free(auth);
		printf("Failed to allocate access token\n");
		exit(-1);
	}
	
	// Try to allocate for consumer key and set	
	auth->access_secret = malloc(strlen(access_secret) * sizeof(char) + 1);
	if (auth->access_secret == NULL) {
		free(auth);
		printf("Failed to allocate access secret\n");
		exit(-1);
	}
	
	// Copy keys to structure
	strcpy(auth->consumer_key, consumer_key);
	strcpy(auth->consumer_secret, consumer_secret);
	strcpy(auth->access_token, access_token);
	strcpy(auth->access_secret, access_secret);
	
	return auth;
}

void twitter_auth_free(TWITTER_AUTH *auth) {
	if (auth != NULL) {
        	free (auth->consumer_key);
		free (auth->consumer_secret);
		free (auth->access_token);
		free (auth->access_secret);
        	free (auth);
	}
}

int update_status(TWITTER_AUTH *auth, char *status) {
	// Check if more than 140 chars 
	if (strlen(status) > 140) {
		printf("A tweet can't be more than 140 characters");
		return -1;
	}
	
	char *status_string = malloc(7 + strlen(status) + 1);
	char *s = "status=";
	strcpy(status_string, s);
	strcat(status_string, status);
	//char *resp = post(UPDATE_URL, oauth_url_escape(status_string));
	free(status_string);
}
