/*
 *
 * Copyright (c) 2014 David Corbin.
 *
 * This library is free software; 
 * you can redistribute it and/or modify
 * it under the terms of the MIT license. 
 * See COPYING for details.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <oauth.h>
#include <curl/curl.h>
#include <json/json.h>

#include "tweet.h"
#include "http_methods.h"

/* Show command arguments */
void 
show_args() 
{
	printf("These are the arguments\n");
	exit(1);
}




/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(json_object *jobj){
  enum json_type type;
  printf("type: ",type);
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  switch (type) {
    case json_type_boolean: printf("json_type_booleann");
			 printf("value: %sn", json_object_get_boolean(jobj)? "true": "false");
			 break;
    case json_type_double: printf("json_type_doublen");
			printf("	  value: %lfn", json_object_get_double(jobj));
			 break;
    case json_type_int: printf("json_type_intn");
			printf("	  value: %dn", json_object_get_int(jobj));
			 break;
    case json_type_string: printf("json_type_stringn");
			 printf("	   value: %sn", json_object_get_string(jobj));
			 break;
  }

}

void json_parse_array( json_object *jobj, char *key) {
  void json_parse(json_object * jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if(key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  printf("Array Length: %dn",arraylen);
  int i;
  json_object * jvalue;

  for (i=0; i< arraylen; i++){
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, NULL);
    }
    else if (type != json_type_object) {
      printf("value[%d]: ",i);
      print_json_value(jvalue);
    }
    else {
      json_parse(jvalue);
    }
  }
}

/*Parsing the json object*/
void json_parse(json_object * jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
    printf("type: ",type);
    type = json_object_get_type(val);
    switch (type) {
      case json_type_boolean: 
      case json_type_double: 
      case json_type_int: 
      case json_type_string: print_json_value(val);
			   break; 
      case json_type_object: printf("json_type_objectn");
			   jobj = json_object_object_get(jobj, key);
			   json_parse(jobj); 
			   break;
      case json_type_array: printf("type: json_type_array, ");
			  json_parse_array(jobj, key);
			  break;
    }
  }
} 




/*
void chr_cstrlit(unsigned char u, char *buffer, size_t buflen)
{
    if (buflen < 2)
	*buffer = '\0';
    else if (isprint(u) && u != '\'' && u != '\"' && u != '\\' && u != '\?')
	sprintf(buffer, "%c", u);
    else if (buflen < 3)
	*buffer = '\0';
    else
    {
	switch (u)
	{
	case '\a':  strcpy(buffer, "\\a"); break;
	case '\b':  strcpy(buffer, "\\b"); break;
	case '\f':  strcpy(buffer, "\\f"); break;
	case '\n':  strcpy(buffer, "\\n"); break;
	case '\r':  strcpy(buffer, "\\r"); break;
	case '\t':  strcpy(buffer, "\\t"); break;
	case '\v':  strcpy(buffer, "\\v"); break;
	case '\\':  strcpy(buffer, "\\\\"); break;
	case '\'':  strcpy(buffer, "\\'"); break;
	case '\"':  strcpy(buffer, "\\\""); break;
	case '\?':  strcpy(buffer, "\\\?"); break;
	default:
	    if (buflen < 5)
		*buffer = '\0';
	    else
		sprintf(buffer, "\\%03o", u);
	    break;
	}
    }
}
*/

char *
unescape(char *escaped, int len) 
{
char *unescaped = malloc(len * sizeof(char));
int j = 0;

int test = 0;

char backslash = "\\";
for (int i = 0; i < len; i++) {
if (escaped[i] == backslash) {
test++;
continue;
} else {
unescaped[j] = escaped[i];
j++;
}
}

printf("%s\n", unescaped);
printf("Test: %i\n", test);

return escaped;
}


int 
main(int argc, char **argv)
{
	struct Memory chunk;

	curl_global_init(CURL_GLOBAL_ALL);
	
	/* No arguments */
	if (argc == 1) {
		show_args();
	}

	for (int i = 1; i < argc; i++) {
		/* Disable peer verification */
		if (strcmp(argv[i], "--no-verify-peer") == 0) {
			peerverify = false;
		}

		/* Print verbosely */
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "verbose") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		}
	}
	
	/* If help menu */
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		show_args();
	}
	
	else if (strcmp(argv[1], "feed") == 0) {
		chunk = get(home_feed_url, peerverify);

chunk.memory = unescape(chunk.memory, (int)chunk.size);

//printf("%s\n", chunk.memory);

//json_object *jobj = json_tokener_parse();
//json_parse(jobj);
	}
	
	/* No correct args */
	else {
		char *status_string = malloc(7 + strlen(argv[1]) + 1);
		char *s = "status=";

		strcpy(status_string, s);
		strcat(status_string, argv[1]);
		chunk = post(tweet_url, oauth_url_escape(status_string), peerverify);
		free(status_string);

printf("%s\n", chunk.memory);

	}

	/* Done */
	curl_global_cleanup();

	/* Free allocated memory */
	if(chunk.memory)
		free(chunk.memory);

	return 0;
}
