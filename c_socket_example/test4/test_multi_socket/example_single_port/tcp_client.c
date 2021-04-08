#include <sys/socket.h>
#include <stdlib.h> //exit
#include <string.h> //memset
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
const char* _PORT = "3345";

void error_handling(char* message);

int main(int argc, char* argv[]){
	printf("waiting-----------\n");

	int client_socket;
	int server_socket;
	struct sockaddr_in server_addr;
	char message[1024] = {0x00, };

	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(client_socket==-1) error_handling("socket error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	////
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(atoi(_PORT));

	if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
		error_handling("connect error");

	write(client_socket, argv[1], sizeof(argv[1]-1));

	if(read(client_socket, message, sizeof(message)-1)==-1)
		error_handling("read error");
	printf("[Server] : %s\n", message);

	while(strcmp(message,"quit") != 0){
		printf("MESSAGE : ");
		scanf("%s",message);
		printf("\n");
		write(client_socket, message, sizeof(message)-1);
	}

	close(client_socket);

	return 0;
}


void error_handling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
