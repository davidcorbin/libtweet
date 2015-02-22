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