#include <stdio.h>
#include <stdlib.h>

#include "../src/tweet.h"
#include "keys.h"

int main(void) {
	TWEET *tweet = tweet_init();
	TWITTER_AUTH *user = twitter_auth_init(getKey("consumerkey"), getKey("consumersecret"), getKey("usertoken"), getKey("usersecret"));
	update_status(user, tweet, "This is a simple example of a tweet!");
	printf("aaaa\n");
	return 0;
}