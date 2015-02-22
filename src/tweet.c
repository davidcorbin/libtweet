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
#include "response.h"

struct auth {
	char *consumer_key;
	char *consumer_secret;
	char *access_token;
	char *access_secret;
};

TWEET_AUTH *tweet_auth_init(char *consumer_key, char *consumer_secret, char *access_token , char *access_secret) {

	// Try to allocate struct
	TWEET_AUTH *auth = malloc(sizeof(TWEET_AUTH));
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

void tweet_auth_free(TWEET_AUTH *auth) {
	if (auth != NULL) {
        	free (auth->consumer_key);
		free (auth->consumer_secret);
		free (auth->access_token);
		free (auth->access_secret);
        	free (auth);
	}
}



struct tweet {
	char *resp;
};

TWEET *tweet_init() {
	TWEET *tweet = malloc(sizeof(TWEET));
	return tweet;
}

TWEET *tweet_update_status(TWEET_AUTH *auth, TWEET *tweet, char *status) {
	char *status_string = malloc(7 + strlen(status) + 1);
	char *s = "status=";
	strcpy(status_string, s);
	strcat(status_string, status);
	tweet->resp = post(UPDATE_URL, oauth_url_escape(status_string), auth->consumer_key, auth->consumer_secret, auth->access_token, auth->access_secret);
	unescape(tweet->resp, '\\');
	free(status_string);
	return tweet;
}

char *tweet_val(char *key, TWEET *tweet) {
	return get_tweet_val(key, tweet->resp);
}

char *tweet_full_resp(TWEET *tweet) {
	return tweet->resp;
}
