//
//  Server.c
//  640Project2
//
//  Created by Zhen Niu on 14-3-28.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//

/* A simple server in the internet domain using TCP
 The port number is passed as an argument *
 */

#include "Server.h"
#include "Message.h"
#include "udpMessage.h"

void error1(char *msg)
{
	perror(msg);
	exit(0);
}

int server(int portno,const char* hostname, int UDP, int force)
{
	int sockfd, newsockfd;

	struct sockaddr_in serv_addr, cli_addr;

	if (UDP==0)
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	else
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0)
		error1("ERROR opening socket\n");
	else printf("Server socket created!\n");



	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	if (strcmp(hostname, "")==0)
	{
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		printf("bind to in addr any\n");
	}
	else
	{
		struct hostent * h;

		if(inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0)
		{
			h=gethostbyname(hostname);
			if (h==NULL)
				error1("set ip address error.\n");
			else memcpy((char *) &serv_addr.sin_addr.s_addr,h->h_addr_list[0], h->h_length);
		}
	}

	serv_addr.sin_port = htons(portno);




	int opt = 1;

	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));


	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0)
		error1("ERROR on binding\n");
	else printf("bind success!\n");
	int begin = 1 ;

	int temp;
	pthread_t thread[2];
	if(UDP == 0 )
	{
		while(force == 1||begin == 1)
		{
			begin = 0;
			listen(sockfd,5);

			unsigned int clilen = sizeof(cli_addr);


			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);


			if (newsockfd < 0)
				error1("ERROR on accept\n");
			else printf("successfully conneted!\n");



			//ServerReceiveThread(newsockfd);
			struct ThreadpassIn * point1 =  ( struct ThreadpassIn *)malloc(sizeof(struct ThreadpassIn));
			//struct ThreadpassIn * point2 = malloc(sizeof(struct ThreadpassIn));
			point1->arg = newsockfd ;
			//point2->arg = newsockfd ;
			point1->forceFlag = force ;
			//point2->forceFlag = force;
			point1->whoreceive = 0;
			//point2->whoreceive = 0 ;
			if(( temp = pthread_create(&thread[0], NULL, SendThread, (void *)point1)) != 0)
				error1("Server Sending Thread Failed!\n");

			if(( temp = pthread_create(&thread[1], NULL, ReceiveThread, (void *)point1)) != 0)
				error1("Server Receiving Thread Failed!\n");



			pthread_join(thread[0], NULL);
			pthread_join(thread[1], NULL);
			//free(point2);
			free(point1);


		}
		return 0;
	}
	else
	{

		//ServerReceiveThread(newsockfd);
		struct UDPThreadpassIn * point1 =  ( struct UDPThreadpassIn *)malloc(sizeof(struct UDPThreadpassIn));

		point1->arg = sockfd ;
		//point2->arg = newsockfd ;
		point1->forceFlag = force ;
		//point2->forceFlag = force;
		point1->whoreceive = 0;
		point1->serv_addr = NULL;
		if(( temp = pthread_create(&thread[0], NULL, SendUDPThread, (void *)point1)) != 0)
			error1("Server Sending Thread Failed!\n");

		if(( temp = pthread_create(&thread[1], NULL, ReceiveUDPThread, (void *)point1)) != 0)
			error1("Server Receiving Thread Failed!\n");

		pthread_join(thread[0], NULL);
		pthread_join(thread[1], NULL);
		free(point1);


	}
}



