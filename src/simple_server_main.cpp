#include "ServerSocket.h"
#include "SocketException.h"
#include <string>

int main ( int argc, int argv[] )
{
	char ctemp[256];
	
  	std::cout << "running....\n";
	int counter;
  try
    {
      // Create the socket
      ServerSocket server (5002);
		counter=0;
      while ( true )
	{

	  ServerSocket new_sock;
	  server.accept ( new_sock );

	  try
	    {
	      while ( true )
			{
			  std::string data;
			  new_sock >> data;
			  //printf("Data masuk: %s\n",data);
			  sprintf(ctemp,"%d",counter);
			  new_sock << ctemp;
			  counter++;
			  
			  if(counter>10000)
			  	counter=0;
			}
	    }
	  catch ( SocketException& ) {}

	}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}

