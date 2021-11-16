/*
 * PalindromeServer.c
 *
 * @since 2019-06-10
 * @author philip gust
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXBUF 128

/**
 * Get listener socket
 *
 * @param port the port number
 * @return listener socket or -1 if unavailable
 */
int get_listener_socket(int port) {
    // Creating internet socket stream file descriptor
    int listen_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock_fd < 0) {
        return -1;
    }

    // SO_REUSEADDR prevents the "address already in use" errors
    // that commonly come up when testing servers.
    int optval = 1;
    if (setsockopt(listen_sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int)) < 0) {
    	close(listen_sock_fd);
    	return -1;
    }

    // host address and port
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    memset(&address, 0, addrlen);
    address.sin_family = AF_INET;  // address from internet
    address.sin_port = htons(port);   // port in network byte order
    address.sin_addr.s_addr = INADDR_ANY;  // bind to any address

    // bind host address to port
    if (bind(listen_sock_fd, (struct sockaddr *)&address, addrlen) < 0) {
    	close(listen_sock_fd);
		return -1;
    }

    // set up queue for clients connections up to default
    // maximum pending socket connections (usually 128)
    if (listen(listen_sock_fd, SOMAXCONN) < 0) {
    	close(listen_sock_fd);
    	return -1;
    }

	return listen_sock_fd;
}

/**
 * Palindrome server listens for connections, reads input strings
 * from socket, and writes palindromes of the string to the socket.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
	char buf[2*MAXBUF];
    struct sockaddr_in address; // connector's address information
    socklen_t addrlen = sizeof address;
    int port;

    // ensure port specified
    if (argc < 2) {
    	fprintf(stderr, "usage: %s port", argv[0]);
    	return EXIT_FAILURE;
    }

    // decode and validate port
    if ((sscanf(argv[1], "%d", &port) != 1) || (port <= 0)) {
		fprintf(stderr, "Invalid port %s\n", argv[1]);
		return EXIT_FAILURE;
	}

    // get listener socket on the port
	int listen_sock_fd = get_listener_socket(port);
	if (listen_sock_fd < 0) {
		perror("listen_sock_fd");
		return EXIT_FAILURE;
	}

	// Since loops forever, relies on OS to flush and close all
	// stdio streams, including listener socket, on system exit.
    while (true) {
        // accept client connection
    	fprintf(stderr, "waiting for connection...\n");
		int sock_fd = accept(listen_sock_fd, (struct sockaddr *)&address, &addrlen);
		if (sock_fd < 0) {
			perror("accept");
			continue;
		}

		// process input line
		FILE* sock_file = fdopen(sock_fd, "r+");
		if ((sock_file != NULL) && (fgets(buf, MAXBUF, sock_file) != NULL)) {
			// bkw_idx selects characters backward from end of input
			// string and fwd_idx adds characters to end of the string
			size_t bkw_idx = strlen(buf);
			if (bkw_idx > 0) {
				if (buf[bkw_idx-1] == '\n') {
					bkw_idx--;  // step over newline
				}
				int fwd_idx = bkw_idx;
				while (bkw_idx > 0) {
					buf[fwd_idx++] = buf[--bkw_idx] ;
				}
				buf[fwd_idx] = '\0';  // terminate string

				// write time to socket
				if (fputs(buf , sock_file) < 0) {
					perror("send");
				}
			}
		}

		// close socket to complete write operation
		fclose(sock_file);
    }
}

