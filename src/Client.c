//
//  Client.c
//  640Project2
//
//  Created by Zhen Niu on 14-3-28.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//


#include "Client.h"
#include "Message.h"
#include "udpMessage.h"

void error2(char *msg)
{
	perror(msg);
	exit(0);
}

int client(int portno, const char * hostname,int UDP,const char* source)
{
	int sockfd;
	struct sockaddr_in serv_addr;
	memset((void*)&serv_addr, 0,sizeof(serv_addr) );


	if (UDP==0)
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	else
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0)
		error2("ERROR opening socket\n");
	else printf("socket opened!\n");
	/*
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(source);
    localaddr.sin_port = portno;  // Any local port will do
    bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr));
	 */
	// initialized to  be  0
	serv_addr.sin_family = AF_INET;

	struct hostent * h;

	h=gethostbyname(hostname);
	if (h==NULL)
	{
		if(inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0)
			error2("set ip address error.\n");
		else printf("get address 1!\n");
	}
	else
	{
		bcopy ( h->h_addr_list[0], &(serv_addr.sin_addr), h->h_length);
		printf("get address2!\n");

	}
	//else memcpy((char *) &serv_addr.sin_addr.s_addr, h->h_addr_list, h->h_length);

	char ** pptr=h->h_addr_list;

	char str[32];
	for(;*pptr!=NULL;pptr++)
		printf(" address:%s/n", inet_ntop(h->h_addrtype, *pptr, str, sizeof(str)));


	serv_addr.sin_port = htons(portno);


	pthread_t thread[2];
	int temp;

	if(UDP == 0 )
	{
		int c = connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
		printf("%d",c);
		if (c < 0)
			error2("ERROR connecting\n");
		else printf("successfully conneted!\n");


		//ClientSendThread(sockfd);

		struct ThreadpassIn * point = malloc(sizeof(struct ThreadpassIn));
		point->arg =sockfd ;
		point->forceFlag = 0;
		point->whoreceive = 1;

		if((temp = pthread_create(&thread[0], NULL, SendThread, (void*)point)) != 0)
			error2("Client Sending Thread Failed!\n");
		if((temp = pthread_create(&thread[1], NULL, ReceiveThread, (void*)point)) != 0)
			error2("Client Receiving Thread Failed!\n");

		pthread_join(thread[1], NULL);
		pthread_join(thread[0], NULL);

		free(point);
		return 0;
	}
	else
	{

		struct UDPThreadpassIn * mythread = malloc(sizeof(struct UDPThreadpassIn ));
		mythread->serv_addr = &serv_addr;
		mythread->forceFlag = 0 ;
		mythread->arg = sockfd ;
		mythread->whoreceive = 1 ;
		if((temp = pthread_create(&thread[0], NULL, SendUDPThread, (void*)mythread)) != 0)
			error2("Client Sending Thread Failed!\n");
		if((temp = pthread_create(&thread[1], NULL, ReceiveUDPThread, (void*)mythread)) != 0)
			error2("Client Receiving Thread Failed!\n");

		pthread_join(thread[1], NULL);
		pthread_join(thread[0], NULL);
		free(mythread);
		close(sockfd);
	}
}





