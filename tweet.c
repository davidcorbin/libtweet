/*
 *
 * Copyright (c) 2014 David Corbin.
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
#include "http_methods.h"
#include "oauth.h"

/* Show command arguments */
void 
show_args() 
{
	printf("These are the arguments\n");
	exit(1);
}

char *
unescape(char *escaped, int len) 
{
char *unescaped = malloc(len * sizeof(char));
int j = 0;

int test = 0;

char backslash[1] = "\\";
for (int i = 0; i < len; i++) {
if (escaped[i] == backslash[0]) {
test++;
continue;
} else {
unescaped[j] = escaped[i];
j++;
}
}

return unescaped;
}


int 
main(int argc, char **argv)
{
	struct Memory chunk;

	curl_global_init(CURL_GLOBAL_ALL);
	
	/* No arguments */
	if (argc == 1) {
		show_args();
	}

	for (int i = 1; i < argc; i++) {
		/* Disable peer verification */
		if (strcmp(argv[i], "--no-verify-peer") == 0) {
			peerverify = false;
		}

		/* Print verbosely */
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "verbose") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		}
	}
	
	/* If help menu */
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		show_args();
	}
	
	else if (strcmp(argv[1], "feed") == 0) {
		chunk = get(home_feed_url, peerverify);

//chunk.memory = unescape(chunk.memory, (int)chunk.size);

printf("%s\n", chunk.memory);

	}
	
	/* No correct args */
	else {
		char *status_string = malloc(7 + strlen(argv[1]) + 1);
		char *s = "status=";

		strcpy(status_string, s);
		strcat(status_string, argv[1]);
		chunk = post(tweet_url, oauth_url_escape(status_string), peerverify);
		free(status_string);

printf("%s\n", chunk.memory);

	}

	/* Done */
	curl_global_cleanup();

	/* Free allocated memory */
	if(chunk.memory)
		free(chunk.memory);

	return 0;
}
