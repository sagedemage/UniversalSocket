/* Client side C/C++ program to demonstrate Socket Programming */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#define SERVER_ADDRESS "127.0.0.1"

int main(int argc, char const* argv[]) {
	int status, client_fd;
	struct sockaddr_in server_address;
	char* msg = "Hello";
	char buffer[1024] = { 0 };

	client_fd =  socket(AF_INET, SOCK_STREAM, 0);

	if (client_fd == -1) {
		printf("Socket creation error \n");
		return -1;
	}

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, SERVER_ADDRESS, &server_address.sin_addr) <= 0) {
		printf("Invalid address: Address not supported \n");
		return -1;
	}

	status = connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address));

	if (status == -1) {
		printf("Connection Failed \n");
		return -1;
	}
	send(client_fd, msg, strlen(msg), 0);
	printf("Sent a message\n");

	// closing the connected socket
	close(client_fd);
	return 0;
}
