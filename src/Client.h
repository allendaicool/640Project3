//
//  Client.h
//  640Project2
//
//  Created by Zhen Niu on 14-3-28.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//

#ifndef Client_640project3
#define Client_640project3
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <climits>
#include <pthread.h>
#include <sys/time.h>
#include "Message.h"

#endif
void error2(char *msg);
int client(int portno, const char * hostname,int UDP,const char* source);




