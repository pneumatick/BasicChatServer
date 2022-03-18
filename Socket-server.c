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
  	int n;

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
	
	// Accept a single awaiting request
	connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
	strcpy(sendBuff, "Client has connected.\n");
	write(connfd, sendBuff, strlen(sendBuff));

        // Main loop 
	while (1) {
		while ((n = read(connfd, sendBuff, sizeof(sendBuff) - 1)) > 0) {
			//sendBuff[n] = 0;
			printf("Message received from %d: %s", connfd, sendBuff);
			write(connfd, sendBuff, strlen(sendBuff));
		}

		if (n < 0) {
			printf("\nRead error\n");
		}

		sleep(1);
	}

	close(connfd);	

	return 0;
}
