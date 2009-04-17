// Definition of the ClientSocket class

#ifndef ClientSocket_class
#define ClientSocket_class

#include <sys/types.h>
#include <sys/socket.h>

#include "Socket.hh"

/*class ClientSocket
{
	ClientSocket(std::string host,int port);
	~ClientSocket();
		
	struct sockaddr_in address;
	int sockfd;
};*/

class ClientSocket : private Socket
{
 public:

	ClientSocket ( std::string host, int port );
	virtual ~ClientSocket(){};

	//int Tutup();
	const ClientSocket& operator << ( const std::string& ) const;
	const ClientSocket& operator >> ( std::string& ) const;

	//int Baca(std::string& data);
	//int Tulis(std::string data);
	
	int send_buffer(char* c,int ukuran);	
	int baca_buffer(char* c);	
};


#endif

