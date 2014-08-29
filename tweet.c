#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <oauth.h>
#include <curl/curl.h>

#include <json/json.h>

#include "tweet.h"


/* CURL response callback */
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct Memory *mem = (struct Memory *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
		printf("Error allocating memory\n");
		return 0;
	}
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

/* Show command arguments */
void 
show_args() {
	printf("These are the arguments\n");
	exit(1);
}

/* Show home feed */
void 
homefeed() {

	CURL *curl;
	CURLcode res;

	chunk.memory = malloc(1); // Will be reallocated
	chunk.size = 0; // Nothing currently

	/* Init CURL */
	curl = curl_easy_init();

	char *signedurl = oauth_sign_url2(home_feed_url, NULL, OA_HMAC, "GET", consumer_key, consumer_secret, user_token, user_secret);

	/* Use the OAuth signed URL */
	curl_easy_setopt(curl, CURLOPT_URL, signedurl);

	if (!peerverify) 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	/* Add response to memory */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* Give chunk to callback */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	/* Execute curl */
	res = curl_easy_perform(curl);

	/* Show Error */
	if(res != CURLE_OK) {
		fprintf(stderr, "Failed: %s\n", curl_easy_strerror(res));
		exit(2);
	}
	else {
		json_object *jobj = json_tokener_parse(chunk.memory);
		//json_parse(jobj);
		//printf("%s\n", chunk.memory);
		printf("Done\n");
	}

	/* Don't leave a mess */
	curl_easy_cleanup(curl);

	/* Free allocated memory */
	if(chunk.memory)
		free(chunk.memory);
}

/* Post new tweet */
void 
post() {
	CURL *curl;
	CURLcode res;

	chunk.memory = malloc(1); // Will be reallocated
	chunk.size = 0; // Nothing currently

	/* Init CURL */
	curl = curl_easy_init();

char *status = oauth_url_escape("status=test");

	char *signedurl = oauth_sign_url2(tweet_url, &status, OA_HMAC, "POST", consumer_key, consumer_secret, user_token, user_secret);

char *reply = oauth_http_post(signedurl, status);
printf("%s\n", reply);


	/* Use the OAuth signed URL */
	curl_easy_setopt(curl, CURLOPT_URL, signedurl);

	curl_easy_setopt(curl, CURLOPT_POST, 1);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, status);

	if (!peerverify) 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	/* Add response to memory */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* Give chunk to callback */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	/* Execute curl */
	res = curl_easy_perform(curl);

	/* Show Error */
	if(res != CURLE_OK) {
		fprintf(stderr, "Failed: %s\n", curl_easy_strerror(res));
		exit(2);
	}
	else {
		json_object *jobj = json_tokener_parse(chunk.memory);
		//json_parse(jobj);
		printf("%s\n", chunk.memory);
		printf("Done\n");
	}

	/* Don't leave a mess */
	curl_easy_cleanup(curl);

	/* Free allocated memory */
	if(chunk.memory)
		free(chunk.memory);
}

/* Parse the arguments */
void 
parse_args(int argc, char **argv) {
	/* Only one argument */
	if (argc == 1) {
		show_args();
	}

	for (int i = 1; i < argc-1; i++) {
		/* Disable peer verification */
		if (strcmp(argv[i], "--no-verify-peer")) {
			peerverify = false;
		}
	}
	
	/* If help menu */
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		show_args();
	}
	
	else if (strcmp(argv[1], "feed") == 0) {
		homefeed();
	}

	else if (strcmp(argv[1], "post") == 0) {
		post();
	}
	
	/* No correct args */
	else {
		show_args();
	}
}


void json_parse(json_object * jobj) {
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
	curl_global_init(CURL_GLOBAL_ALL);
	
	parse_args(argc, argv);

	/* Done */
	curl_global_cleanup();

	return 0;
}