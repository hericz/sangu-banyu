//SIMPLE MAIN CLIENT.h
//

#ifndef simple_main_client_h
#define simple_main_client_h

//int main_client (std::string host,int port_num);

int main_client (std::string host,int port_num,char* buf);
int main_client_stack(std::string host,int port_num,char* buf,int no_stack);
int main_client_sendbuf(std::string host,int port_num,char* buf,int ukuran);
#endif //simple_main_client_h
