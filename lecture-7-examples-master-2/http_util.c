/*
 * http_util.c
 *
 * Functions used to implement http operations.
 *
 *  @since 2019-04-10
 *  @author: Philip Gust
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "http_server.h"
#include "http_util.h"


/** The default response protocol */
static const char* responseProtocol = "HTTP/1.1";

/**
 * Reads line of request from request stream and trims trailing CRLF.
 *
 * @param istream the socket input stream
 * @param buf the buffer to read into
 * @param len the length of the buffer
 * @return the buffer point of line read, else NULL
 */
char* readRequestLine(FILE *istream, char buf[], int len) {
	if (fgets(buf, len, istream) == NULL) {
		return NULL;
	}
	// trim newline characters
	char* p = strstr(buf, CRLF);
	if (p != NULL) {
		*p = 0;
	}
	return buf;
}

/**
 * Converts timer to a RFC-1123 formatted date-time string
 * of the form: Sat, 13 Apr 2019 19:03:32 GMT
 *
 * @param timer the time
 * @param buf the buffer
 */
static inline void milliTimeToRFC_1123_Date_Time(time_t timer, char buf[]) {
	strftime(buf, 64, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&timer));
}

/**
 * Send status and fixed properties to response output stream.
 *
 * @param ostream the output socket stream
 * @param status the response status
 * @param statusMsg the response message
 */
void sendResponseStatus(FILE *ostream, int status, const char* statusMsg) {
	fprintf(ostream, "%s %d %s%s", responseProtocol, status, statusMsg, CRLF);
	if (debug) {
		fprintf(stderr, "< %s %d %s\n", responseProtocol, status, statusMsg);
	}

	// send server name
	sendResponseProperty(ostream, "Server", "Tiny Http Server");

	// send response time
	char time_str[MAXBUF];
	milliTimeToRFC_1123_Date_Time(time(NULL), time_str);
	sendResponseProperty(ostream, "Date", time_str);
}

/**
 * Send property to response output stream.
 *
 * @param ostream the output socket stream
 * @param propName property name
 * @param propVal property value;
 */
void sendResponseProperty(FILE *ostream, char name[], char value[]) {
	fprintf(ostream, "%s: %s%s", name, value, CRLF);
	if (debug) {
		fprintf(stderr, "< %s: %s\n", name, value);
	}
}

/**
 * Send end of response properties to response output stream.
 *
 * @param ostream the output socket stream
 * @param propName property name
 * @param propVal property value;
 */
void endResponseProperties(FILE *ostream) {
	fprintf(ostream, "%s", CRLF);
	if (debug) {
		fprintf(stderr, "< \n");
	}
}

/**
 * Copy bytes from content stream to output stream.
 *
 * @param contentStream the content stream
 * @param ostream the output stream
 * @param nbytes the number of bytes to send
 */
void sendResponseBytes(FILE *contentStream, FILE *ostream, unsigned long nbytes) {
	// copy content stream to output stream
    for (unsigned long byte; (nbytes > 0) && !feof(contentStream); nbytes--) {
    	byte = fgetc(contentStream);
    	fputc(byte, ostream);
    }
}

/**
 * Set error response and error page to the response output stream.
 *
 * @param ostream the output socket stream
 * @param status the response status
 * @param statusMsg the response message
 * @param responseHeaders the response headers
 */
void sendErrorResponse(FILE* ostream, int responseCode, const char* responseStr) {
	char errorBody[MAXBUF];  // because of data substitution.
	char errBodyLen[MAXBUF];
	const char* errorPage =
		"<html>"
	    "<head><title>%d %s</title></head>"
	    "<body>%d %s</body>"
	    "</html>";
	sprintf(errorBody, errorPage, responseCode, responseStr, responseCode, responseStr);
	sprintf(errBodyLen, "%zu", strlen(errorBody));

	// send response header
	sendResponseStatus(ostream, responseCode, responseStr);
	sendResponseProperty(ostream, "Content-type", "text/html");
	sendResponseProperty(ostream, "Content-Length", errBodyLen);
	endResponseProperties(ostream);

	// send error body
	fprintf(ostream, "%s", errorBody);
}

/**
 * Resolves server URI to file system path.
 * @param uri the request URI
 * @param fspath the file system path
 */
void resolveUri(const char uri[], char fspath[]) {
	strcpy(fspath, CONTENT_BASE);
	strcat(fspath, uri);
	return;
}

/**
 * Get content type of file path.
 *
 * @param filePath the file path
 * @param contentType the content type
 */
void getContentType(char filePath[], char contentType[]) {
	// file path suffix to content type mapping
	static const char* contentTypes[][2] = {
		{".html", "text/html"},
		{".txt", "text/plain"},
		{".css", "text/css"},
		{".gif", "impage/gif"},
		{".jpg", "image.jpg"},
		{".png", "image.png"},
		{".ico", "image/ico"},
		{ NULL, "application/octet-stream"}  // default
	};
	int i;
	for (i = 0; contentTypes[i][0] != NULL; i++) {
		if (strcasestr(filePath, contentTypes[i][0]) != NULL) break;
	}
	strcpy(contentType, contentTypes[i][1]);
}

