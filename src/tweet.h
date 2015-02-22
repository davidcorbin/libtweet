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

#ifndef _LIBTWEET_H_
#define _LIBTWEET_H_

#define UPDATE_URL "https://api.twitter.com/1.1/statuses/update.json"
#define HOME_TIMELINE_URL "https://api.twitter.com/1.1/statuses/home_timeline.json"

typedef struct auth TWEET_AUTH;
typedef struct tweet TWEET;

TWEET_AUTH * tweet_auth_init(char *consumer_key, char *consumer_secret, char *access_token , char *access_secret);

void tweet_auth_free(TWEET_AUTH *auth);

TWEET *tweet_init();

TWEET *tweet_update_status(TWEET_AUTH *auth, TWEET *object, char *status);

char *tweet_val(char *key, TWEET *tweet);

#endif
