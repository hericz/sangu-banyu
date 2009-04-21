/* Simple_client_main
 * Program utama client untuk pengambilan data dari modul
 * 
 */

#include "ClientSocket.h"
#include "SocketException.h"
#include "simple_main_client.h"
#include <iostream>
#include <string>

int main_client ()
{

	  try
		{

				ClientSocket client_socket ( "localhost", 5002 );

				std::string reply;

				try
				{
					client_socket << "Test message.";
					client_socket >> reply;
				}
				catch ( SocketException& ) 
				{
					return 1;
				}

				std::cout << "We received this response from the server:" << reply << "\n";
				//client_socket->Tutup();
			
		}
	  catch ( SocketException& e )
		{
		  std::cout << "ERROR\nException was caught:" << e.description() << "\n";
		}
  return 0;
}

