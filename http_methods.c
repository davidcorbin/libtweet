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

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STDBOOL_H_
#include <stdbool.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef __CURL_CURL_H
#include <curl/curl.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>

#include "error_desc.h"
#include "http_methods.h"
#include "oauth.h"

void
initDir() {
        char *home = getenv("HOME");
        char *tweet = strcat(home, "/.tweet");
        mkdir(tweet, 0775);
        dir = realloc(dir, strlen(tweet) + 1);
        dir = tweet;
}

/*** Functions for getting Twitter credentials from file ***/
char *
getConsumerKey() {
        char *buff = malloc(50*sizeof(char));
	//FILE *fp = fopen(strcat(dir, "/consumerkey"), "a+");
	FILE *fp = fopen("/home_users/pico42553/.tweet/usersecret", "a+");

	if (fp == NULL) {
	 	perror("Read Error:");
	}
        else {
	        fscanf(fp, "%s", buff);
	        printf("consumer key:%s\n", buff);
	        fclose(fp);
        }
	return buff;
}
char *
getConsumerSecret() {
        char *buff = malloc(50*sizeof(char));
        printf("%s\n", dir);
printf("%s\n", strcat(dir, "/consumersecret"));
        FILE *fp = fopen(strcat(dir, "/consumersecret"), "a+");
        if (fp == NULL) {
                perror("Read Error:");
        }
        else {
                fscanf(fp, "%s", buff);
                //printf("%s\n", buff);
                fclose(fp);
        }
        return buff;
}
char *
getUserToken() {
        char *buff = malloc(50*sizeof(char));
printf("%s\n", strcat(dir, "/usertoken"));
        FILE *fp = fopen(strcat(dir, "/usertoken"), "a+");
        if (fp == NULL) {
                perror("Read Error:");
        }
        else {
                fscanf(fp, "%s", buff);
                //printf("%s\n", buff);
                fclose(fp);
        }
        return buff;
}
char *
getUserSecret() {
        char *buff = malloc(50*sizeof(char));
printf("%s\n", strcat(dir, "/usersecret"));
        FILE *fp = fopen(strcat(dir, "/usersecret"), "a+");
        if (fp == NULL) {
                perror("Read Error:");
        }
        else {
                fscanf(fp, "%s", buff);
                //printf("%s\n", buff);
                fclose(fp);
        }
        return buff;
}

/*** Functions for setting Twitter credentials in file ***/
void 
setConsumerKey(char *key) {
	FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/consumerkey"), "w");
	if (fp == NULL) {
		perror("Write Error:");
	}
	else {
		fputs(key, fp);
		fclose(fp);
	}
}
void 
setConsumerSecret(char *key) {
        FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/consumersecret"), "w");
        if (fp == NULL) {
                perror("Write Error:");
        }
        else {
                fputs(key, fp);
                fclose(fp);
        }
}
void 
setUserToken(char *key) {
        FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/usertoken"), "w");
	if (fp == NULL) {
                perror("Write Error:");
        }
        else {
                fputs(key, fp);
                fclose(fp);
        }
}
void 
setUserSecret(char *key) {
        FILE *fp = fopen(strcat(getenv("HOME"), "/.tweet/usersecret"), "w");
	if (fp == NULL) {
                perror("Write Error:");
	}
        else {
                fputs(key, fp);
                fclose(fp);
        }
}

/* CURL response callback */
static size_t
write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
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

/* Show home feed */
struct Memory 
get(char *url, bool peerverify) 
{

        CURL *curl;
        CURLcode res;

struct Memory chunk;

        chunk.memory = malloc(1); // Will be reallocated
        chunk.size = 0; // Nothing currently

        /* Init CURL */
        curl = curl_easy_init();

        char *signedurl = oauth_sign_url2(url, NULL, OA_HMAC, "GET", (char *)getConsumerKey(), (char *)getConsumerSecret(), (char *)getUserToken(), (char *)getUserSecret());

        /* Use the OAuth signed URL */
        curl_easy_setopt(curl, CURLOPT_URL, signedurl);

        if (!peerverify) 
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        /* Add response to memory */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);

        /* Give chunk to callback */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Execute curl */
        res = curl_easy_perform(curl);

        /* Show Error */
        if(res != CURLE_OK) {
                fprintf(stderr, "Failed: %s\n", curl_easy_strerror(res));
                error_desc((int)res);
                exit(2);
        }

        /* Don't leave a mess */
        curl_easy_cleanup(curl);

return chunk;
}


struct Memory
post(char *url, char *url_enc_args, bool peerverify)
{
        CURL *curl;
        CURLcode res;

struct Memory chunk;

        struct curl_slist *slist = NULL;
        char * ser_url, **argv, *auth_params, auth_header[1024], 
*non_auth_params, *final_url, *temp_url, *postdata;
        int argc;

        chunk.memory = malloc(1); // Will be reallocated
        chunk.size = 0; // Nothing currently

        ser_url = (char *) malloc(strlen(url) + strlen(url_enc_args) + 2);
        sprintf(ser_url, "%s?%s", url, url_enc_args);

        argv = malloc(0);
        argc = oauth_split_url_parameters(ser_url, &argv);
        free(ser_url);

        temp_url = oauth_sign_array2(&argc, &argv, NULL, OA_HMAC, 
"POST", (char *)getConsumerKey(), (char *)getConsumerSecret(), (char *)getUserToken(), (char *)getUserSecret());
        free(temp_url);

        auth_params = oauth_serialize_url_sep(argc, 1, argv, ", ", 6);
        sprintf( auth_header, "Authorization: OAuth %s", auth_params );
        slist = curl_slist_append(slist, auth_header);
        free(auth_params);

        non_auth_params = oauth_serialize_url_sep(argc, 1, argv, "", 1 );

        final_url = (char *) malloc( strlen(url) + strlen(non_auth_params) );

        strcpy(final_url, url);

        postdata = non_auth_params;

        for (int i = 0; i < argc; i++) {
                free(argv[i]);   
        }

        free(argv);

        curl = curl_easy_init();

        if (peerverify == false) 
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);

        /* Add response to memory */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);

        /* Give chunk to callback */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
                fprintf(stderr, "Failed: %s\n", curl_easy_strerror(res));
                error_desc((int)res);
                exit(2);
        }

        curl_easy_cleanup(curl);

return chunk;
}