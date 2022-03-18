#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
 
int main(void) {
	int listenfd = 0; // Socket file descriptor
	int connfd = 0;   // Accepted request file descriptor
  
	struct sockaddr_in serv_addr;

	char sendBuff[1025];  
	int numrv;  

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Success: Socket retrieved\n");

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;    
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serv_addr.sin_port = htons(5000);
	
	// Bind the server address to the socket
	// aka "assigning a name to the socket"
	bind(listenfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	if (listen(listenfd, 10) == -1) {
		printf("Failed to listen\n");
		return -1;
	}     

        // Main loop 
	while(1) {      
		connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // Accept awaiting request
	
		strcpy(sendBuff, "Client has connected.\n");
		write(connfd, sendBuff, strlen(sendBuff));

		close(connfd);    
		sleep(1);
	} 

	return 0;
}
