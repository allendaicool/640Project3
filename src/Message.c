//
//  SendAndReceive.c
//  640Project2
//
//  Created by Zhen Niu on 14-3-30.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//


#include "Message.h"

void * SendThread(void * point)
{
	struct ThreadpassIn * pointstr = (struct ThreadpassIn *) point;

	char c;

	while (1) {

		c=fgetc(stdin);
		char  buffer[256]={c};
		int l=255;
		// whoSend == 0 is server  whosend == 1 is the client
		if(c==EOF && pointstr->whoreceive == 0 && pointstr->forceFlag == 1 )
		{
			char temp = c;
			send(pointstr->arg, &temp, 1,0);
			break;
		}
		if(c==EOF)
		{
			shutdown(pointstr->arg,2);
			exit(0);
			break;
		}
		else
		{
			char temp[255];
			bzero(temp,255);
			fgets(temp,l,stdin);
			strcat(buffer,temp);
			send(pointstr->arg, buffer, l,0);
		}
	}
}

void *ReceiveThread(void* point)
{
	struct ThreadpassIn * pointstr = (struct ThreadpassIn *) point;
	int sockfd = pointstr->arg;

	while (1) {

		char buffer[256];
		bzero(buffer,256);
		//printf("receive message from client:\n");
		size_t n=recv(sockfd, buffer, 255,0);
        printf("bloooock\n");
		if (n>0)
		{
			if(  pointstr->whoreceive == 1 && buffer[0] ==EOF )
			{
				shutdown(sockfd,2);
				exit(0);
				break;
			}
			fputs(buffer,stdout);
		}
		else
		{
			// server has to return to the listening state with the force flag set
			if(pointstr->whoreceive == 0 && n==0 && pointstr->forceFlag == 1)
			{
				break;
			}

			shutdown(sockfd,2);

			exit(0);
			break;
		}

	}

}

