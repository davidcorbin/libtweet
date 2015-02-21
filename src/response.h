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

struct Tweet {
        char *memory;
        size_t size;
};

typedef struct Tweet tweet;

char *get_tweet_val(char *key, char *twitter_resp);
char *feed(char *twitter_resp);

void unescape(char *str, char garbage);
