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

#ifndef _STDIO_H_
#include <stdio.h>
#endif

void 
error_desc(int error) 
{
        //printf("%i\n", error);

        /* Host name verification problem */
        if (error == 6)
                printf("Fix: Connect to an working Internet connection that allows access to api.twitter.com\n");

        /* Peer certificate problem */
        if (error == 60)
                printf("Fix: Try using --no-verify-peer\n");
}