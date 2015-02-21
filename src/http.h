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

struct Memory post(char *url, char *url_enc_args);
struct Memory get(char *url);
