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
#include <sys/types.h>
#include <string.h>		
#include <stdlib.h>

static void *xmalloc_fatal(size_t size) {
	if (size==0) return NULL;
	fprintf(stderr, "Out of memory.");
	exit(1);
}

void *xmalloc (size_t size) {
	void *ptr = malloc (size);
	if (ptr == NULL) return xmalloc_fatal(size);
	return ptr;
}

void *xcalloc (size_t nmemb, size_t size) {
	void *ptr = calloc (nmemb, size);
	if (ptr == NULL) return xmalloc_fatal(nmemb*size);
	return ptr;
}

void *xrealloc (void *ptr, size_t size) {
	void *p = realloc (ptr, size);
	if (p == NULL) return xmalloc_fatal(size);
	return p;
}

char *xstrdup (const char *s) {
	void *ptr = xmalloc(strlen(s)+1);
	strcpy (ptr, s);
	return (char*) ptr;
}

void xfree(void *ptr) {
	return free(ptr);
}
// vi: sts=2 sw=2 ts=2
