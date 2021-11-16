/*
 * DateServer.c
 *
 *  @since 2018-08-07
 *  @author philip gust
 *  @modified: 2019-06-18 by zach rooney
 */
#include <stdbool.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 9091
#define MAXBUF 80

/**
 * This program acts as a server that makes a palindrome out of what the
 * client sends.
 *
 * @return EXIT_SUCCESS if successful
 */
int main(void) {

    // Creating internet socket stream file descriptor
    int listener_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_sock_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // attach socket to port PORT
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    memset(&address, 0, addrlen);
    address.sin_family = AF_INET;  // address from internet
    address.sin_port = htons(PORT);   // port in network byte order
    address.sin_addr.s_addr = INADDR_ANY;  // bind to any address

    // bind host address to port
    if (bind(listener_sock_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // set up queue for clients connections up to default
    // maximum pending socket connections (usually 128)
    if (listen(listener_sock_fd, SOMAXCONN) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // accept client connection
    	fprintf(stderr, "connection?\n");
		int socket_fd = accept(listener_sock_fd, (struct sockaddr *)&address, &addrlen);
		if (socket_fd < 0) {
			perror("accept");
			continue;
		}
        fprintf(stderr, "got one! %d\n", ntohs(address.sin_port));

        // char arrays for palindrome
        char input[80], output[160];

        // read string
        if (read(socket_fd, input, MAXBUF) < 0) {
            	perror("read error");
            }
        else {

			// copying input string
			strcpy(output, input);

			// add reverse of input string to output string	w/o newline in the middle
			int temp = strlen(input) - 1;
			for (int pos = (strlen(input) - 2); pos >= 0; pos--) {
				output[temp] = input[pos];
				temp++;
			}

			// send palindrome and write new line
			if (write(socket_fd, output, strlen(output) + 1) < 0) {
				perror("send");
			}
			if (write(socket_fd, "\n", 2) < 0) {
				perror("send newline");
			}

		}
		// close socket to complete write operation
		close(socket_fd);
    }

    // close server socket
    close(listener_sock_fd);
    return 0;
}

