//============================================================================
// Name        : UDPNetworking.cpp
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
	cout << "Begin Server" << endl;

	SISA_NET::UDP_Handler * j = UDP_Handler::CreateInstant();
	j->InitSocket();
	j->Bind();

	while(1)
	{
		byte buffer[100];
		j->Block_Rec(buffer);
	}
	return 0;
}

