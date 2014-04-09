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



void * SendUDPThread(void * point)
{
	struct UDPThreadpassIn * pointstr = (struct UDPThreadpassIn *) point;
	int Isclient = pointstr->whoreceive ;
	char c;
	char blockBuffer[256];
	int paste = 0 ;
	int flush = 0 ;
	while (1) {
		int l=255;

		if(Isclient == 0 &&ClientAddr !=0 && flush ==0)
		{
			if( sendto(pointstr->arg, blockBuffer,l,0,(struct sockaddr * )(ClientAddr),sizeof(struct sockaddr_in )) == -1)
			{
				perror("sendTo failed");
				exit(0);
				break;
			}
			flush  = 1 ;
		}
		c=fgetc(stdin);
		char  buffer[256]={c};
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
					strcat(blockBuffer, &c);
					paste = 1 ;
				}
				char temp[255];
				bzero(temp,255);
				fgets(temp,l,stdin);
				strcat(blockBuffer,temp);
			}
			else {
				char temp[255];
				bzero(temp,255);
				fgets(temp,l,stdin);
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
		if( (n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *)&pointer, &addrlen))==-1)
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

