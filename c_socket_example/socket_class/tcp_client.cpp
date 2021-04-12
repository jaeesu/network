#include "./tcp_client.h"

void tcpclientsocket::start(char* _PORT, char* _name){
	socket = socket(PF_INET, SOCK_STREAM, 0);
	if(socket == -1) error_handling("socket error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(atoi(_PORT));

	if(connect(socket, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1) error_handling("connect error");

	write(socket, _name, sizeof(_name)-1);

	close(socket);
}


void error_handling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(){
	printf("starting client socket.........");
	tcpclientsocket client_socket;
	client_socket.start();

}
