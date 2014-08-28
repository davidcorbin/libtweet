#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oauth.h>
#include <curl/curl.h>

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
void homefeed() {

}

/* Parse the arguments */
void 
parse_args(int argc, char **argv) {
	/* Only one argument */
	if (argc == 1) {
		show_args();
	}
	
	/* If help menu */
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		show_args();
	}
	
	else if (strcmp(argv[1], "home") == 0) {
		homefeed();
	}
}


int 
main(int argc, char **argv)
{
	parse_args(argc, argv);

	chunk.memory = malloc(1); // Will be reallocated
	chunk.size = 0; // Nothing currently

	char *url = "https://api.twitter.com/1.1/statuses/home_timeline.json";

	char *signedurl = oauth_sign_url2(url, NULL, OA_HMAC, "GET", consumer_key, consumer_secret, user_token, user_secret);

	curl_global_init(CURL_GLOBAL_ALL);

	/* Init CURL */
	curl = curl_easy_init();

	/* Use the OAuth signed URL */
	curl_easy_setopt(curl, CURLOPT_URL, signedurl);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	/* Add response to memory */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* Give chunk to callback */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	/* Execute curl */
	res = curl_easy_perform(curl);

	/* Show Error */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}
	else {
		//printf("%s", chunk.memory);
		printf("Done");
	}

	/* Don't leave a mess */
	curl_easy_cleanup(curl);

	/* Free allocated memory */
	if(chunk.memory)
		free(chunk.memory);

	/* Done with curl */
	curl_global_cleanup();

	return 0;
}