/*
 * http_methods.c
 *
 * Functions that implement HTTP methods, including GET
 *
 *  @since 2019-04-10
 *  @author: Philip Gust
 */


#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

#include "http_methods.h"
#include "http_server.h"
#include "http_util.h"

/**
 * Handle GET request.
 *
 * @param the socket stream
 * @param uri the request URI
 * @param requestHeaders the request headers
 * @param responseHeaders the response headers
 */
void do_get(FILE *ostream, const char uri[]) {
	// resolve uri to system file path
	char filePath[MAXBUF];
	resolveUri(uri, filePath);

	// open file to read
	FILE *contentStream = fopen(filePath, "rb");
	if (contentStream == NULL) {
		sendErrorResponse(ostream, 404, "Not Found");
		return;
	}

	// get size and other file info file
	struct stat sb;
	fstat(fileno(contentStream), &sb);  // fileno() gets fd from FILE*
	unsigned long nbytes = (unsigned long)sb.st_size;

	// output response header
	sendResponseStatus(ostream, 200, "OK");

	char contentType[MAXBUF];
	getContentType(filePath, contentType);
	sendResponseProperty(ostream, "Content-type", contentType);

	char contentLength[MAXBUF];
	sprintf(contentLength, "%lu", nbytes);
	sendResponseProperty(ostream, "Content-Length", contentLength);

	endResponseProperties(ostream);   // end of response properties


	// output response bytes
	sendResponseBytes(contentStream, ostream, nbytes);
	fclose(contentStream);
}
