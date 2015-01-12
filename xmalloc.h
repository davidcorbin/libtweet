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

#ifndef _OAUTH_XMALLOC_H
#define _OAUTH_XMALLOC_H      1 

/* Prototypes for functions defined in xmalloc.c  */
void *xmalloc (size_t size);
void *xcalloc (size_t nmemb, size_t size);
void *xrealloc (void *ptr, size_t size);
char *xstrdup (const char *s);
void xfree(void *ptr);

#endif
