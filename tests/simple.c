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

#include "../src/tweet.h"
#include "keys.h"

int main(void) {
	TWEET *tweet = tweet_init();
	TWEET_AUTH *user = tweet_auth_init(getKey("consumerkey"), getKey("consumersecret"), getKey("usertoken"), getKey("usersecret"));
	tweet = tweet_update_status(user, tweet, "This is a simple example of a tweet!");
	//printf("%s\n", tweet->resp);
	tweet_auth_free(user);
	return 0;
}