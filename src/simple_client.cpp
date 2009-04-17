#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, int argv[] )
{
	std::string ip;
	int port;
	
	ip="192.168.1.32";
	port=5002;
	try
	{
		printf("Connecting ke port: %d",port);
		ClientSocket client_socket (ip, port );

		std::string reply;
		//while(1)
		//{
			try
			{
				client_socket << "info";
				client_socket >> reply;
			}
			catch ( SocketException& ) 
			{}

			std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;
		//}
	}
	catch ( SocketException& e )
	{
	std::cout << "Exception was caught:" << e.description() << "\n";
	}

  return 0;
}

