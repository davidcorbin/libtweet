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

#define UPDATE_URL "https://api.twitter.com/1.1/statuses/update.json"
#define HOME_TIMELINE_URL "https://api.twitter.com/1.1/statuses/home_timeline.json"

typedef struct auth TWITTER_AUTH;
typedef struct tweet TWEET;

TWITTER_AUTH * twitter_auth_init(char *consumer_key, char *consumer_secret, char *access_token , char *access_secret);

void twitter_auth_free(TWITTER_AUTH *auth);

int update_status(TWITTER_AUTH *auth, TWEET *object, char *status);

#endif
