//
//  Client.h
//  640Project2
//
//  Created by Zhen Niu on 14-3-28.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//

#ifndef message_640project3
#define message_640project3
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
struct ThreadpassIn{
	int arg ;
	int  whoreceive;
	int forceFlag;
};
#endif


void * SendThread(void* point);
void * ReceiveThread(void*  point2);




