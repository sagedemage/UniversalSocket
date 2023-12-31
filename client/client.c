/* Client side C/C++ program to demonstrate Socket Programming */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

/*	
* The server address can be changed 
* - use 127.0.0.1 if you are testing on the loopback address
* - use server's external address if you are dealing with an external server
*/
//#define SERVER_ADDRESS "127.0.0.1"

#define SERVER_ADDRESS "192.168.1.72"


static struct sockaddr_in setup_address() {
	/* Setup Address */
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	return server_address;
}

static struct sockaddr_in convert_address_to_binary(struct sockaddr_in server_address) {
	/* Convert IPv4 or IPv6 network address to binary */
	// It performs the conversion from text to binary form
	if (inet_pton(AF_INET, SERVER_ADDRESS, &server_address.sin_addr) <= 0) {
		printf("Invalid address: Address not supported \n");
		exit(0);
	}
	return server_address;
}

int main() {
	int connection_status, client_fd;
	ssize_t send_status;
	struct sockaddr_in server_address;
	char* msg = "Hello";

	// Create the socket
	client_fd =  socket(AF_INET, SOCK_STREAM, 0);

	if (client_fd == -1) {
		printf("Socket creation error \n");
		return -1;
	}

	server_address = setup_address();

	server_address = convert_address_to_binary(server_address);

	// Open connection to socket
	connection_status = connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address));

	if (connection_status == -1) {
		char msg[] = "Connection Failed!";
		printf("\033[31m%s\033[0m\n", msg);
		return -1;
	}

	// Send a message to socket
	send_status = send(client_fd, msg, strlen(msg), 0);

	if (send_status == -1) {
		printf("Sending a message failed\n");
		return -1;
	}
	else {
		char msg[] = "Sent a message to the server!";
		printf("\033[32m%s\033[0m\n", msg);
	}

	// close the connected socket
	close(client_fd);

	return 0;
}
