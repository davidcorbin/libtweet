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





 char *request(char *http_method, char *url, char *url_enc_args)
 {
CURL *curl;
  struct curl_slist * slist = NULL;
  char * ser_url, **argv, *auth_params, auth_header[1024], *non_auth_params, *final_url, *temp_url;
  int argc;

char *postdata;

  ser_url = (char *) malloc(strlen(url) + strlen(url_enc_args) + 2);
  sprintf(ser_url, "%s?%s", url, url_enc_args);

  argv = malloc(0);
  argc = oauth_split_url_parameters(ser_url, &argv);
  free(ser_url);

  temp_url = oauth_sign_array2(&argc, &argv, NULL, OA_HMAC, http_method, consumer_key, consumer_secret, user_token, user_secret);
  free(temp_url);

  auth_params = oauth_serialize_url_sep(argc, 1, argv, ", ", 6);
  sprintf( auth_header, "Authorization: OAuth %s", auth_params );
  slist = curl_slist_append(slist, auth_header);
  free(auth_params);

  non_auth_params = oauth_serialize_url_sep(argc, 1, argv, "", 1 );

  final_url = (char *) malloc( strlen(url) + strlen(non_auth_params) );

  strcpy(final_url, url);

  postdata = non_auth_params;

/*
  for (int i = 0; i < argc; i++ )
  {
    free(argv[i]);   
  }
*/
  free(argv);


  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
  curl_easy_setopt(curl, CURLOPT_POST, 1);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);

 int curlstatus = curl_easy_perform(curl); /* Execute the request! */

 curl_easy_cleanup(curl);
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

char *status = oauth_url_escape("status=Test tweet");

	char *signedurl = oauth_sign_url2(tweet_url, NULL, OA_HMAC, "POST", consumer_key, consumer_secret, user_token, user_secret);

printf("%s\n\n", signedurl);

printf("%s\n\n", status);

char *asdf = malloc(100 * sizeof(char));
asdf = strcat(signedurl, "&");
char *asdfg = malloc(150 * sizeof(char));
asdfg = strcat(asdf, status);

printf("%s\n", asdfg);

	/* Use the OAuth signed URL */
	curl_easy_setopt(curl, CURLOPT_URL, asdfg);

//free(asdf);
//free(asdfg);

	curl_easy_setopt(curl, CURLOPT_POST, 1L);

	//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, status);

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
		request("POST", tweet_url, oauth_url_escape("status=aaa"));
//printf("%s\n", resp);
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