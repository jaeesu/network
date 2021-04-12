#include "./tcp_server.h"
//#include "./tcp_client.h"
#include <sys/socket.h>

void tcpserversocket::start(char* _PORT){
	this->socket = socket(PF_INET, SOCK_STREAM, 0);
	int client_socket; 
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	client_addr_size = sizeof(client_addr);

	if(socket == -1) error_handling("socket error\n");

	memset(&this->addr, 0, sizeof(this->addr));
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->addr.sin_port = htons(atoi(_PORT));
	
	if(bind(socket, (struct sockaddr*) &this->addr, sizeof(this->addr)) == -1)
		error_handling("bind error");

	if(listen(this->socket, 5)==-1) error_handling("listen error");
	client_socket = accept(this->socket, (struct sockaddr*)&client_addr, &client_addr_size);
	if(client_socket == -1) error_handling("accept error");
	char name[20];
	read(client_socket, name, sizeof(name)-1);
	printf("%s\n\n", name);

	close(client_socket);
	close(this->socket);


}


void error_handling((char*) _msg){
	fputs(_msg, stderr);
	fputc('\n', stderr);
	printf("exit : %u", (unsigned int)pthread_self());
	pthread_exit(NULL);
	//exit(1);
}


int main(){
	tcpserversocket socket();
	socket->start();
	return 0;

}
