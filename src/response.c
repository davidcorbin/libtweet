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

char *
unescape(char *escaped, int len) 
{
	char *unescaped = malloc(len * sizeof(char));
	int j = 0, test = 0;
	char backslash[1] = "\\";
	for (int i = 0; i < len; i++) {
		if (escaped[i] == backslash[0]) {
			test++;
			continue;
		} else {
			unescaped[j] = escaped[i];
			j++;
		}
	}
	return unescaped;
}