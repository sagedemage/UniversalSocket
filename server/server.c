/* Server side C/C++ program to demostrate Socket Programming */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	int buffer[1024] = { 0 };

	// Setup Address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Creating socket file descriptor
	// SOCKET
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	// BIND
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// LISTEN
	if (listen(server_fd, 3) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	while(true) {
		// ACCEPT
		new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

 		if (new_socket == -1) {
        	perror("accept");
        	exit(EXIT_FAILURE);
    	}

		// Read buffer
		read(new_socket, buffer, 1024);
		char* msg = (char*)buffer;
		printf("%s\n", msg);
	}

	// closing the connected socket
	close(new_socket);

	return 0;
}
