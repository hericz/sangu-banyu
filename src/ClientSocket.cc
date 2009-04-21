// Implementation of the ClientSocket class

#include "ClientSocket.hh"
#include "SocketException.hh"


ClientSocket::ClientSocket ( std::string host, int port )
{

//printf("Connecting to port %d.....",port);
  if ( ! Socket::create() )
    {
		throw SocketException ( "ERROR: Could not create client socket.\n" );
    }

  	if ( ! Socket::connect ( host, port ) )
    {
		throw SocketException ( "ERROR: Could not bind to port.\n" );
    }
    
    //printf("OK\n");
}

const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
	
  if (!Socket::send ( s ))
    {
		throw SocketException ( "ERROR: Could not write to socket.\n" );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
		throw SocketException ( "ERROR: Could not read from socket.\n" );
    }

  return *this;
}

int ClientSocket::baca_buffer(char* c)
{
	int jumlah_terima;
  	if ( ! (jumlah_terima=Socket::recv_buffer(c)) )
    {
		throw SocketException ( "ERROR: Could not read from socket.\n" );
		return -1;
    }
	
	return jumlah_terima;
}

int ClientSocket::send_buffer(char* c,int ukuran)
{
	if (!Socket::send_buf (c,ukuran) )
    {
      throw SocketException ( "Could not write to socket." );
    }
	return ukuran; 
}

