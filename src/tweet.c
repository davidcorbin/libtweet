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
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>

#include "tweet.h"
#include "http.h"
#include "oauth.h"
#include "keys.h"
#include "response.h"

/* Show command arguments */
void show_args() 
{
	const char* args = 
		"usage: tweet \"#twittercli is awesome\"\n"
		"  tweet \"#twittercli is awesome!\"\n";
	printf("%s", args);
	exit(0);
}

int main(int argc, char **argv)
{
	struct Memory chunk;

	curl_global_init(CURL_GLOBAL_ALL);
	
	/* No arguments */
	if (argc == 1) {
		show_args();
	}

	for (int i = 1; i < argc; i++) {
		/* Print verbosely */
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "verbose") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		}
	}

	/* Set Twitter consumer key */
	if (strcmp(argv[1], "setconsumerkey") == 0) {
		setConsumerKey(argv[2]);
		exit(0);
	}
	/* Set Twitter consumer secret */
	if (strcmp(argv[1], "setconsumersecret") == 0) {
		setConsumerSecret(argv[2]);
		exit(0);
	}
	/* Set Twitter user token */
	if (strcmp(argv[1], "setusertoken") == 0) {
		setUserToken(argv[2]);
		exit(0);
	}
	/* Set Twitter user secret */
	if (strcmp(argv[1], "setusersecret") == 0) {
		setUserSecret(argv[2]);
		exit(0);
	}
	
	/* If help menu */
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		show_args();
	}
	
	else if (strcmp(argv[1], "feed") == 0) {
		chunk = get(home_feed_url);
		unescape(chunk.memory, '\\');
		
		feed(chunk.memory);
		
		//printf("%s\n", chunk.memory);
	}
	
	/* Post tweet */
	else {
		/* Check if more than 140 chars */
		if (strlen(argv[1]) > 140) {
			printf("A tweet can't be more than 140 characters");
			exit(1);
		}
		char *status_string = malloc(7 + strlen(argv[1]) + 1);
		char *s = "status=";

		strcpy(status_string, s);
		strcat(status_string, argv[1]);
		chunk = post(tweet_url, oauth_url_escape(status_string));
		free(status_string);

		unescape(chunk.memory, '\\');
		
		printf("%s (@%s)\n", get_tweet_val("screen_name", chunk.memory), get_tweet_val("name", chunk.memory));
		printf("   %s\n", get_tweet_val("text", chunk.memory));
	}

	/* Done */
	curl_global_cleanup();

	/* Free allocated memory */
	if(chunk.memory)
		free(chunk.memory);

	return 0;
}
