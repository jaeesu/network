#include "./tcp_server.h"
//#include "./tcp_client.h"
#include <sys/socket.h>
#include <vector>
#include "./tcp_client.h"

const char* MAIN_PORT = "3345";

void tcpserversocket::start(char* _PORT){
	_socket = socket(PF_INET, SOCK_STREAM, 0);
	tcpclientsocket client;

	vector<int> client_thread;

	if(_socket == -1) error_handling("socket error\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(atoi(_PORT));
	
	if(bind(_socket, (struct sockaddr*) &addr, sizeof(addr)) == -1)
		error_handling("bind error");

	if(listen(_socket, 5)==-1) error_handling("listen error");

	client.set_socket(accept(_socket, client.get_addr(), client.get_addr_size()));

	//build_thread
	//주소값 어떻게 넘겨주냐......
	client_thread.push_back(0);
	client_thread.back() = build_thread((pthread_t*)&client_thread.back(), build_connection, (void*)client.get_socket());

	if(client.get_socket() == -1) error_handling("accept error");

	char name[20];
	read(client.get_socket(), name, sizeof(name)-1);
	printf("client connected : %s\n\n", name);

	close(client.get_socket());
	close(_socket);
}


void error_handling(string _msg){
	char msg[100];
	strcpy(msg, _msg.c_str());
	fputs(msg, stderr);
	fputc('\n', stderr);
	printf("exit : %u", (unsigned int)pthread_self());
	pthread_exit(NULL);
	//exit(1);
}

pthread_t build_thread(pthread_t* _addr, void* _func, void* _argv){
	pthread_t tid;
	tid = pthread_create(_addr, NULL, _func, _argv);
	if(tid <0){
		perror("thread create error : ");
		exit(0);
	}
	//exiting creating thread

	return tid;
}

void* build_connection(void* _argv){
	//@param _argv : client_socket
	//server_socket은 어떻게 넘겨줘...... - 결국 배열 써야되는거..?
	//client socket을 아예 클래스 객체로 넘겨줘야 하나??

	printf("pid : %u, tid : %x \n", (unsigned int)getpid(), (unsigned int)pthread_self());

	time_t ct;
	struct tm tm;
	ct=time(NULL);
	tm=*localtime(&ct);

	char name[20];
	printf("enter you name : ");
	scanf("%s", name);

	unsigned long int client_socket = *(int*)_argv;

	if(client_socket==-1) error_handling("accept error");
	read(client_socket, name, sizeof(name)-1);

	printf("[ client : %s ....connected ]\n", name);

	char msg[] = "this is server in test4\n";

	write(client_socket, msg, sizeof(msg));

	while(strcmp(msg, "quit") != 0){
		while(read(client_socket, msg, sizeof(msg)-1)==-1 || str_len(msg)<=24) {} //error_handling("read error");
		printf("[ %d : %d : %d ] [client : %s]%s  \n", tm.tm_hour, tm.tm_min, tm.tm_sec, name, msg);
		write(client_socket, msg, sizeof(msg)-1);
	}
	//전송자말고 다른 클라이언트들에 브로드캐스트 해주는 코드 작성
	//클라이언트 정보를 배열 같은 곳에 저장해둬야 한다.

	printf("[ client : %s ....disconnected ]\n", name);

	close(client_socket);

	return 0;

}

int str_len(char* _str){
	int cnt;
	for(int i=0;i<strlen(_str);i++){
		if(!isspace(_str[i])) cnt++;
	}
	return cnt;
}


int main(){
	tcpserversocket server;
	server.start((char*)MAIN_PORT);
	return 0;

}
