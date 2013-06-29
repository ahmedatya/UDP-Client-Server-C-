/*
 * UDPHandler.cpp
 *
 *  Created on: Jun 28, 2013
 *      Author: aatya
 */

#include "UDPHandler.h"

namespace SISA_NET {

/*Init Static Members*/
UDP_Handler * UDP_Handler ::instance = NULL;


UDP_Handler::UDP_Handler() {
	// Set the port number to the default value
	port_num = DEF_PORT;
	socket_id = -1;
	debug_flag = true;
}

UDP_Handler::~UDP_Handler() {
	// TODO Auto-generated destructor stub
}


UDP_Handler * UDP_Handler::CreateInstant()
{
	if (instance == NULL)
		instance = new UDP_Handler();

	return instance;
}

STATE UDP_Handler::InitSocket()
{
	// Create UDP Socket on a the specified port
	if ((socket_id=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
	    return FAIL;
	}
	// Now the port is ready to be used
	return SUCC;
}

/*
 * The IP Address format has to be "10.x.x.x"
 * Bind the Socket for the server
 */
STATE UDP_Handler::Bind()
{
	struct sockaddr_in s_addr;

	// Generic ip address filling
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port_num);
	s_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(s_addr.sin_zero),8);


	// Bind the socket to ip address. Hence, accept connections from any ip at this port
	if(bind(socket_id , (struct sockaddr*)&s_addr, sizeof(struct sockaddr) ) == -1)
	{
		return FAIL;
	}

	if(debug_flag)
	{
		printf("\nUDPServer Waiting for client on port %d with sock = %d\n",port_num,socket_id);
		fflush(stdout);

	}
	// Now the port is ready to be used
	return SUCC;
}

/*
 * The IP Address format has to be "10.x.x.x"
 */
uint32 UDP_Handler::Block_Rec (byte * buffer, uint32 max_length)
{
	if(this->socket_id == -1) return 0;
	struct sockaddr_in server_addr , client_addr;

	int  addr_len = sizeof(struct sockaddr);
	int len = recvfrom(this->socket_id, buffer, max_length, 0,  (struct sockaddr *)&client_addr, (socklen_t*)&addr_len) ;
	printf("length = %d \n",len);

	if(connections[client_addr.sin_port].byte_recv_num == 0)
	{
		connections[client_addr.sin_port].port_num = client_addr.sin_port;
		connections[client_addr.sin_port].ip_addr = new char[strlen(inet_ntoa(client_addr.sin_addr))];
		strcpy(connections[client_addr.sin_port].ip_addr ,inet_ntoa(client_addr.sin_addr));
	}

	// Updates the number of received bytes
	connections[client_addr.sin_port].byte_recv_num+= len;


	if(this->debug_flag)
	{
		printf("Received packet from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		printf("Data: %s\n" , buffer);
		fflush(stdout);
	}
	return len;
}

/*
 * The IP Address format has to be "10.x.x.x"
 */
uint32 UDP_Handler::Receive(byte * buffer, uint32 max_length, char * ip_addr)
{
	if(this->socket_id == -1)
			return 0;

		struct sockaddr_in s_addr;

		// Init the address structure with zeros
		memset((char *) &s_addr, 0, sizeof(s_addr));

		// Generic ip address filling
		s_addr.sin_family = AF_INET;
		s_addr.sin_port = htons(this->port_num);

		if(strcmp(ip_addr,"XXX"))
		{
			if (inet_aton(ip_addr, &s_addr.sin_addr) == 0)  // Create datagram with server IP and port.
			{
				return ERR;
			}
		}
		else
		{
			s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		}

		uint32 len = 0;
		len = recv(this->socket_id, buffer, max_length, 0);   // read datagram from server socket

		if(len < 0)
		{
			//Something wrong happened
			return 0;
		}

		if(connections[s_addr.sin_port].byte_recv_num == 0)
			{
				connections[s_addr.sin_port].port_num = s_addr.sin_port;
				connections[s_addr.sin_port].ip_addr = new char[strlen(inet_ntoa(s_addr.sin_addr))];
				strcpy(connections[s_addr.sin_port].ip_addr,inet_ntoa(s_addr.sin_addr));
			}

			// Updates the number of received bytes
			connections[s_addr.sin_port].byte_recv_num+= len;

		if(this->debug_flag)
		{
			printf("Received packet from %s:%d\n", inet_ntoa(s_addr.sin_addr), ntohs(s_addr.sin_port));
			printf("Data: %s\n" , buffer);
			fflush(stdout);
		}
		return len;
}


/*
 * The IP Address format has to be "10.x.x.x"
 */
STATE UDP_Handler::Send(byte * buffer, uint32 buffer_len, char * ip_addr)
{
	struct sockaddr_in s_addr;
	struct hostent *host;

	// Generic ip address filling
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(this->port_num);

	host= (struct hostent *) gethostbyname(ip_addr);
	s_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(s_addr.sin_zero),8);

	sendto(this->socket_id, buffer, buffer_len, 0, (struct sockaddr*) &s_addr, sizeof(struct sockaddr));

	return SUCC;
}

/*
 * Return the port number for specific IP
 * TODO: Need optimization.
 */
uint16 UDP_Handler::GetPeer(char * ip)
{
	for( map<uint16, Peer>::iterator ii=this->connections.begin(); ii!=this->connections.end(); ++ii)
	{
		if(strcmp((*ii).second.ip_addr,ip))
		{
			return (*ii).first;
		}
	}

	return 0;
}

STATE UDP_Handler::CloseSocket()
{

	return SUCC;
}


} /* namespace SISA_NET */

