//
//  main.c
//  640Project2
//
//  Created by Zhen Niu on 14-3-28.
//  Copyright (c) 2014年 Zhen Niu. All rights reserved.
//


#include "Client.h"
#include "Server.h"
#include <cstring>
#include <climits>

int main(int argc, const char * argv[])
{


	int listen=0;
	int UDP=0;
	const char* source="";
	const char* hostname="";
	int portno=atoi(argv[argc-1]);
	int num=argc;
	int force = 0 ;
	int i=1;
	for(i=1;i<num-1;i++)
	{
		const char* option=argv[i];
		if (strcmp(option,"-l")==0)
		{
			listen = 1;
			continue;
		}
		else if( strcmp(option, "-k")==0)
		{
			printf("sdafdsf");
			force = 1 ;
			continue ;
		}
		else if (strcmp(option,"-s")==0)
		{
			source=argv[i+1];
			i++;
			continue;
		}
		else if (strcmp(option,"-u")==0)
		{
			UDP=1;
			continue;
		}
		else if(i==argc-2)
		{
			hostname=argv[argc-2];
		}
	}
	printf("%d\n",UDP);
	printf("%d\n",portno);
	printf("%s\n",source);
	printf("%s\n",hostname);
	printf("%d\n",listen);

	if(portno<1025 |portno>65535)
	{
		printf("port number should between 1025 to 65535\n");
		exit(0);
	}
	if(force == 1 && listen == 0 )
	{
		printf("should be used only if -l is given\n");
		exit(0);
	}
	if(listen==0 & strcmp(hostname,"")==0)
	{
		printf("please input hostname\n");
		exit(0);
	}

	if(listen==1 & strcmp(source,"")!=0)
	{
		printf("-s can only be used when -l is given\n");
		exit(0);
	}


	if(listen==0)
	{
		client(portno, hostname,UDP,source);
	}
	else
	{
		server(portno, hostname,UDP,force);
	}


	/*if (strcmp(argv[1],"-l")==0) {
        printf("server: \n");

        server(atoi(argv[2]));
    }
    else
    {
        printf("client:\n");
        client(atoi(argv[2]),argv[1]);
    }

    return 0;*/

}
