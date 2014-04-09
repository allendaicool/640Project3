//
//  Server.h
//  640Project2
//
//  Created by Zhen Niu on 14-3-28.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//
#ifndef Server_640project3
#define Server_640project3

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <sys/time.h>
#include <cstring>
#include <climits>
#include "Message.h"

#endif

void error1(char *msg);

int server(int portno,const char* hostname, int UDP,int force);

