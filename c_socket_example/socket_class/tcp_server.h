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

void error_handling(char*);

class tcpserversocket{
	private:
		unsigned long int socket;
		struct sockaddr_in addr;

	public:
		void start(char*);

};


