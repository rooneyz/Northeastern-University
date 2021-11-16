/*
 * http_server.c
 *
 * The HTTP server main function sets up the listener socket
 * and dispatches client requests to request sockets.
 *
 *  @since 2019-04-10
 *  @author: Philip Gust
 */
#include <stdbool.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "http_request.h"
#include "http_server.h"
#include "network_util.h"


#define DEFAULT_HTTP_PORT 1500
#define MIN_PORT 1000

/** debug flag */
const bool debug = true;

/** subdirectory of application home directory for web content */
const char *CONTENT_BASE = "content";

/**
 * Main program starts the server and processes requests
 * @param argv[1]: optional port number (default: 1500)
 */
int main(int argc, char* argv[argc]) {
	int port = DEFAULT_HTTP_PORT;
    struct sockaddr_in address; // connector's address information
    socklen_t addrlen = sizeof address;

    if (argc == 2) {
		if ((sscanf(argv[1], "%d", &port) != 1) || (port < MIN_PORT)) {
			fprintf(stderr, "Invalid port %s\n", argv[1]);
			return EXIT_FAILURE;
		}
	}

    // get listener socket on the default port
	int listen_sock_fd = get_listener_socket(port);
	if (listen_sock_fd == 0) {
		perror("listen_sock_fd");
		return EXIT_FAILURE;
	}

	fprintf(stderr, "Tiny Http Server running on port %d\n", port);

	while (true) {
        // accept client connection
		int socket_fd = accept(listen_sock_fd, (struct sockaddr *)&address, &addrlen);
		if (socket_fd < 0) {
			perror("accept");
			continue;
		}
		if (debug) {
			fprintf(stderr, "New connection accepted  %s:%u\n",
					inet_ntoa(address.sin_addr), ntohs(address.sin_port));
		}

		// handle request
		process_request(socket_fd);
    }

    // close listener socket
    close(listen_sock_fd);
    return EXIT_SUCCESS;

}
