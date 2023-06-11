/* Server side C/C++ program to demostrate Socket Programming */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#define PORT 8080

static struct sockaddr_in setup_address() {
	/* Setup Address */
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	return address;
}

static char* read_buffer(int new_socket, int buffer[1024]) {
	/* Read the buffer */
	read(new_socket, buffer, 1024);
	return (char*)buffer;
}

int main() {
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
	int buf[1024] = { 0 };
	char* msg;

	// Setup Address
	address = setup_address();

	// Create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Set the socket options
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	// Bind address to the socket
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// Listen for connections
	if (listen(server_fd, 3) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	while(true) {
		// Accept for connections
		new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

 		if (new_socket == -1) {
        	perror("accept");
        	exit(EXIT_FAILURE);
    	}

		// Read the buffer
		//read(new_socket, buf, 1024);
		//msg = (char*)buf;

		msg = read_buffer(new_socket, buf);

		printf("%s\n", msg);
	}
}
