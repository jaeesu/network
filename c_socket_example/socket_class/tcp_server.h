#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <iostream>
#include <string.h>

using namespace std;

void error_handling(string);

pthread_t build_thread(pthread_t*, void*, void*);

void* build_connection(void*);

int str_len(char*);

class tcpserversocket{
	private:
		unsigned long int _socket;
		struct sockaddr_in addr;

	public:
		void start(char*);

};

