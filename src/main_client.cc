/* Simple_client_main
 * Program utama client untuk pengambilan data dari modul
 * 
 */

#include "ClientSocket.hh"
#include "SocketException.hh"
#include "main_client.hh"
#include <iostream>
#include <string> 

char data_terima[1024];

int main_client (std::string host,int port_num,char* buf)
{
	int jumlah_terima;
	  try
		{
				ClientSocket client_socket(host,port_num);
				std::string reply;

				try
				{
					client_socket << "sampurasun";
					//client_socket >> reply;
					//printf("Baca buffer...");
					jumlah_terima=client_socket.baca_buffer((char*)&data_terima[0]);
					//printf("OK: %d bytes\n",jumlah_terima);
				}
				catch ( SocketException& )	
				{
					return -1;	
				}
				memcpy(buf,data_terima,jumlah_terima);
				
				//Jika ingin ditampilkan
				//printf("Response:[%d]\n",jumlah_terima);
		}
	  	catch(SocketException& e)
		{
		  std::cout << "ERROR\nException was caught:" << e.description() << "\n";
			return -1;
		}
  	return jumlah_terima;
}

int main_client_stack(std::string host,int port_num,char* buf,int no_stack)
{
	int jumlah_terima;
	  try
		{
				ClientSocket client_socket(host,port_num);
				std::string reply;

				try
				{
					if(no_stack==1)
						client_socket << "stack_01";
					else if(no_stack==2)
						client_socket << "stack_02";
					else if(no_stack==3)
						client_socket << "stack_03";
					else if(no_stack==4)
						client_socket << "stack_04";
					else
						client_socket << "stack_05";
					
					jumlah_terima=client_socket.baca_buffer((char*)&data_terima[0]);
					//printf("OK: %d bytes\n",jumlah_terima);
				}
				catch ( SocketException& ) 
				{
					return -1;
				}
				memcpy(buf,data_terima,jumlah_terima);
				
				//Jika ingin ditampilkan
				//printf("Response:[%d]\n",jumlah_terima);

		}
	  	catch ( SocketException& e )
		{
		  std::cout << "ERROR\nException was caught:" << e.description() << "\n";
			return -1;
		}
  return jumlah_terima;
}

int main_client_sendbuf(std::string host,int port_num,char* buf,int ukuran)
{
	int jumlah_terima;
	  try
		{
				ClientSocket client_socket(host,port_num);
				std::string reply;

				try
				{
					printf("%s:%d kirim data: stack_01\n",host.c_str(),port_num);
					//jumlah_terima=client_socket.send_buffer((char*)buf,ukuran);
					client_socket << "stack_01";
					//jumlah_terima=client_socket.baca_buffer((char*)&data_terima[0]);
					//printf("OK: %d bytes\n",jumlah_terima);
				}
				catch ( SocketException& ) 
				{
					return -1;
				}
				//memcpy(buf,data_terima,jumlah_terima);
				
				//Jika ingin ditampilkan
				//printf("Response:[%d]\n",jumlah_terima);
		}
	  catch ( SocketException& e )
		{
		  std::cout << "ERROR\nException was caught:" << e.description() << "\n";
			return -1;
		} 
  return jumlah_terima;
}

