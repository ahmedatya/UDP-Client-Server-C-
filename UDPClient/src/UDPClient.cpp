//============================================================================
// Name        : UDPClient.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "UDPHandler.h"
using namespace SISA_NET;

int main() {
	cout << "Begin Client\n Enter Msg: \n" << endl; // prints !!!Hello World!!!
	SISA_NET::UDP_Handler * j = UDP_Handler::CreateInstant();
	j->InitSocket();

	char msg[100];
	while(strcmp(msg,"quit"))
	{
		gets(msg);
		j->Send((byte *)msg,strlen(msg), (char *)"127.0.0.1");
	}

	return 0;
}
