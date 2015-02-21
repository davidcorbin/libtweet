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

extern struct Memory {
        char *memory;
        size_t size;
} chunk;

char *get(char *url, char *consumer_key, char *consumer_secret, char *access_token, char *access_secret);

char *post(char *url, char *url_enc_args, char *consumer_key, char *consumer_secret, char *access_token, char *access_secret);
