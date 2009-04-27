// Implementation of the ServerSocket class

#include "ServerSocket.h"
#include "SocketException.h"


ServerSocket::ServerSocket ( int port )
{
	printf("Buat service di port: %d...",port);
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create server socket." );
    }

  if ( ! Socket::bind ( port ) )
    {
      throw SocketException ( "Could not bind to port." );
    }

  if ( ! Socket::listen() )
    {
      throw SocketException ( "Could not listen to socket." );
    }
	printf("OK\n");
}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
//const ServerSocket& ServerSocket::operator << (const char* data_kirim,int ukuran) const
{
  if ( ! Socket::send (s) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}
int ServerSocket::send_buffer(char* c,int ukuran)
{
	
	if (!Socket::send_buf (c,ukuran) )
    {
      throw SocketException ( "Could not write to socket." );
    }
	return ukuran; 
}

const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
  if ( ! Socket::accept ( sock ) )
    {
      throw SocketException ( "Could not accept socket." );
    }
}

