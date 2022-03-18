#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
 
int main() {
	int sockfd = 0; 		// Socket file descriptor
	int n = 0;
	char sendBuff[1024];
	char recvBuff[1025];
	struct sockaddr_in serv_addr;

	// Initialize all elements of recvBuff to zero
	memset(sendBuff, '0', sizeof(sendBuff));
	memset(recvBuff, '0', sizeof(recvBuff));

	// Initialize the socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error : Could not create socket \n");
		return 1;
	}

	// Provide socket structure with domain, port, and address data 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Attempt to connect to the server
	if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        	printf("\nError: Connection failed\n");
		return 1;
	}

	while (1) {
		// Read messages from the server 
		while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0) {
			recvBuff[n] = 0;
			
			// Display server message
			printf("Message from server: ");
			if (fputs(recvBuff, stdout) == EOF) {
				printf("\n Error : Fputs error");
	      		}
	      		printf("\n");


			// Send messages to the server
			printf("Message: ");
			fgets(sendBuff, sizeof(sendBuff), stdin);
			write(sockfd, sendBuff, strlen(sendBuff));

		}
	 
	  	if (n < 0) {
	      		printf("\nRead error\n");
	    	}
  	}
 
	return 0;
}
