/* Client side C/C++ program to demonstrate Socket Programming */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* hello = "Hello";
	char buffer[1024] = { 0 };

	if ((client_fd =  socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("Invalid address\ Address not supported \n");
		return -1;
	}

	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		printf("Connection Failed \n");
		return -1;
	}
	send(client_fd, hello, strlen(hello), 0);
	printf("Sent a message\n");

	// closing the connected socket
	close(client_fd);
	return 0;
}