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

#ifndef _TWITTERCLI_H_
#define _TWITTERCLI_H_

int update_status(char *status);

typedef struct {
	char *consumer_key;
	char *consumer_secret;
	char *access_token;
	char *access_secret;
} TWITTER_AUTH;

//typedef struct auth *twitter_auth;

TWITTER_AUTH * twitter_auth_init(char *consumer_key, char *consumer_secret, char *access_token , char *access_secret);

#endif