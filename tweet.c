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
#include <oauth.h>
#include <curl/curl.h>
#include <json/json.h>

#include "tweet.h"
#include "http_methods.h"

/* Show command arguments */
void 
show_args() 
{
	printf("These are the arguments\n");
	exit(1);
}


void json_parse(json_object * jobj) 
{
	enum json_type type;
	json_object_object_foreach(jobj, key, val) {
		type = json_object_get_type(val);
		switch (type) {
			case json_type_null: printf("json_type_null\n");
 break;
 case json_type_boolean: printf("json_type_boolean\n");
 break;
 case json_type_double: printf("json_type_double\n");
 break;
 case json_type_int: printf("json_type_int\n");
 break;
 case json_type_object: printf("json_type_objectn");
 break;
 case json_type_array: printf("json_type_arrayn");
 break;
 case json_type_string: printf("json_type_stringn");
 break;
		}
	}
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
