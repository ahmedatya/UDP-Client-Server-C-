/*
 * UDPHandler.h
 *
 *  Created on: Jun 28, 2013
 *      Author: aatya
 */

#ifndef UDPHANDLER_H_
#define UDPHANDLER_H_

/*
 * C++ Headers
 */
#include <stdio.h>
#include <string.h>
#include <map>
#include <map>
#include <utility>
using namespace std;


// Socket and Network Headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<arpa/inet.h>


namespace SISA_NET {

/*
 * Data Types redefinitions
 */

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;

/*
 * Enumeration Contains all the network and connection status
 */

enum STATE
{
	 SUCC,
	 FAIL,
	 ERR,
};


struct Peer
{
	uint16 port_num;
	char * ip_addr;
	uint32 byte_sent_num;
	uint32 byte_recv_num;
};

/*
 * Default Values
 */
#define DEF_PORT 8888
#define DEF_LENGTH 1024
/*
 * Singleton Class that Handles all the UDP connections, sending and receiving data.
 */
class UDP_Handler {

private:
	static UDP_Handler * instance;
	UDP_Handler();
	uint16 port_num;
	int socket_id;
	bool debug_flag;
	map<uint16, Peer> connections;

public:

	// Create and/or Get UDP_handler instance.
	static UDP_Handler * CreateInstant();
	// TODO Setters and Getters  functions

	//Open, Init and Bind to a socket (Any address) and return the STATE of the connection
	STATE InitSocket();
	//Open, Init and Bind to a socket (ip_addr address) and return the STATE of the connection
	STATE Bind();

	// Blocking Receive Function that waits till a data is available on the socket. If data is available
	// the function return the data in the buffer pointer and the data length if this function is called with
	// Init a valid socket it returns 0 immediately if error occurs it returns 0 as well
	uint32 Block_Rec (byte * buffer, uint32 max_length = DEF_LENGTH);

	// UnBlocking Receive
	uint32 Receive(byte * buffer, uint32 max_length = DEF_LENGTH, char * ip_addr = "XXX");

	// Transmit data to a certain IP address and return the state of the transmission
	STATE Send(byte * byffer, uint32 buffer_len, char * ip_addr);

	//Utilities TODO: functions can be moved to separate class
	uint16 GetPeer(char * ip);

	// Close socket and free everything
	STATE CloseSocket();

	virtual ~UDP_Handler();
};

} /* namespace SISA_NET */
#endif /* UDPHANDLER_H_ */
