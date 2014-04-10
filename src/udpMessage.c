/*
 * udpMessage.c
 *
 *  Created on: Apr 5, 2014
 *      Author: yihong
 */


//
//  SendAndReceive.c
//  640Project2
//
//  Created by Zhen Niu on 14-3-30.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//


#include "udpMessage.h"

struct sockaddr_in  * ClientAddr =NULL ;
char blockBuffer[256] ={0};
int paste = 0 ;

int  SendUDPBuffer(void *point)
{
	struct UDPThreadpassIn * pointstr = (struct UDPThreadpassIn *) point;
	int l = 256;
	if( sendto(pointstr->arg, blockBuffer,l,0,(struct sockaddr * )(ClientAddr),sizeof(struct sockaddr_in )) == -1)
	{
		perror("sendTo failed");
		exit(0);
	}
	return 1 ;
}


void * SendUDPThread(void * point)
{
	struct UDPThreadpassIn * pointstr = (struct UDPThreadpassIn *) point;
	int Isclient = pointstr->whoreceive ;
	char c;

	while (1) {
		int l=255;

		//if(!(paste== 1 && Isclient == 0 && flush==0)) //
		//{
		c=fgetc(stdin);
		//}
		// whoSend == 0 is server  whosend == 1 is the client
		if(c == EOF )
		{
			break;
		}
		else
		{
			if(Isclient == 0 &&ClientAddr== 0 )
			{
				if(  paste == 0)
				{
					bzero(blockBuffer,256);
					//blockBuffer[0] = c;
					paste = 1 ;
				}
				char temp[255];
				bzero(temp,255);
				fgets(temp,l,stdin);
				//printf(temp);
				strncat(blockBuffer,&c,1);
				strcat(blockBuffer,temp);
			}
			else {
				char  buffer[256]={c};
				char temp[255];
				bzero(temp,255);
				fgets(temp,l,stdin);
				//printf("should be working\n");
				//printf(temp);
				//printf("\n");
				strcat(buffer,temp);
				if(Isclient ==1 )
				{
					if( sendto(pointstr->arg, buffer,l,0,(struct sockaddr * )(pointstr->serv_addr),sizeof(struct sockaddr_in)) == -1)
					{
						perror("sendTo failed !!!!!!");
						exit(0);
						break;
					}
				}
				else
				{
					if( sendto(pointstr->arg, buffer,l,0,(struct sockaddr * )(ClientAddr),sizeof(struct sockaddr_in)) == -1)
					{
						perror("sendTo failed");
						exit(0);
						break;
					}
				}
			}
		}
	}
}

void *ReceiveUDPThread(void* point)
{
	struct UDPThreadpassIn * pointstr = (struct UDPThreadpassIn *) point;
	int sockfd = pointstr->arg;
	int isClient = pointstr->whoreceive ;

	while (1) {

		char buffer[256];
		bzero(buffer,256);
		//printf("receive message from client:\n");
		struct sockaddr_in pointer ;
		socklen_t addrlen = sizeof(pointer);
		size_t n;
		if( (n = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *)&pointer, &addrlen))==-1)
		{
			perror("led");
			exit(0);
			break;
		}

		if (n>0)
		{
			if(pointstr->whoreceive == 0 && ClientAddr == 0)
			{

				ClientAddr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
				ClientAddr->sin_addr = pointer.sin_addr;
				ClientAddr->sin_family = pointer.sin_family;
				ClientAddr->sin_port = pointer.sin_port;
				if(blockBuffer[0]!=0)
				{
					SendUDPBuffer(point);
				}
			}
			fputs(buffer,stdout);

		}
		else
		{

			shutdown(sockfd,2);

			exit(0);
			break;
		}

	}

}

