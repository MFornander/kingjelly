/*
 * NetworkState.cpp
 *
 *  Created on: May 29, 2014
 *      Author: jellydev
 */

#include <src/NetworkState.h>

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

NetworkState::NetworkState() 
{
	struct sockaddr_in server;// = {AF_INET, INADDR_ANY,30000};

	// open a UDP socket
	m_sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sock < 0) 
	{	
		printf("Error Opening socket\n");
	}
    bzero(&server,sizeof(server));
   
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(30000);

    if (bind(m_sock,(struct sockaddr *)&server,sizeof(server))<0)
    { 
        printf(" Error Binding\n");
	}	

	printf("Opened UDP socket on port %d\n", ntohs(server.sin_port) );
}

NetworkState::~NetworkState() 
{
	close(m_sock);
}

void NetworkState::Update()
{
	int                	n = 0;
    char 				buf[128];

    struct foo 
    {
    	bool s;
    	unsigned char pot0;
    	unsigned char pot1;
    	unsigned char pot2;
    	unsigned char pot3;
    } data;

	// read data from socket and update state 
	n = recv(m_sock,buf,128,MSG_DONTWAIT);
	if (n > 0)
	{
		// need to fix the case where we have more than one packet pending
		printf("Received %d bytes\n", n);
		memcpy(&data, buf, n);
		printf("%d %d %d %d %d\n", data.s, data.pot0,data.pot1,data.pot2,data.pot3);

		m_switch = data.s;
		m_pots[0] = data.pot0/255.0;
		m_pots[1] = data.pot1/255.0;
		m_pots[2] = data.pot2/255.0;
		m_pots[2] = data.pot3/255.0;
	}
}