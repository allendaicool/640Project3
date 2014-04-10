/*
 * udpMessage.h
 *
 *  Created on: Apr 5, 2014
 *      Author: yihong
 */

#ifndef UDPMESSAGE_H_
#define UDPMESSAGE_H_
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
struct UDPThreadpassIn{
	int arg ;
	int  whoreceive;
	int forceFlag;
	struct sockaddr_in  * serv_addr;
};

#endif /* UDPMESSAGE_H_ */
void * SendUDPThread(void* point);
void * ReceiveUDPThread(void*  point2);
int  SendUDPBuffer(void *point);
