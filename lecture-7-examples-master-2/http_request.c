/*
 * http_request.c
 *
 * Functions used to process requests from clients.
 *
 *  @since 2019-04-10
 *  @author: Philip Gust
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "http_methods.h"
#include "http_server.h"
#include "http_util.h"


/**
 *  Process an http request.
 *
 *  @param sock_fd the socket descriptor
 */
void process_request(int sock_fd) {
	char buf[MAXBUF];
	char method[MAXBUF];
	char uri[MAXBUF];
	char version[MAXBUF];

	// open socket as a stream
	FILE *stream = fdopen(sock_fd, "rb+");
	if (stream == NULL) {
		perror("fdopen");
		return;
	}

	// get request
	if (readRequestLine(stream, buf, MAXBUF) == NULL) {
		if (debug) {
			fprintf(stderr, "request header empty\n");
		}
		sendErrorResponse(stream, 400, "Bad Request");
		return;
	}

	// decode request fields
	if (sscanf(buf, "%s %s %s", method, uri, version) != 3) {
		if (debug) {
			fprintf(stderr, "request header incomplete: %s\n", buf);
		}
		sendErrorResponse(stream, 400, "Bad Request");
		return;
	}

	// skip request properties up to empty line
	do {
		if (debug) {
			fprintf(stderr, "> %s\n", buf);
		}
	} while ((readRequestLine(stream, buf, MAXBUF) != NULL) && (strlen(buf) > 0));
	if (debug) {
		fprintf(stderr, "> \n");
	}

	// dispatch based on method
	if (strcasecmp(method, "GET") == 0) {
		do_get(stream, uri);  // execute GET method
	} else {
		sendErrorResponse(stream, 501, "Not Implemented");
	}

	// close socket stream
	fflush(stream);
	fclose(stream);
	close(sock_fd);
}

