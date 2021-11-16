/*
 * http_util.h
 *
 * Functions used to implement http operations.
 *
 *  @since 2019-04-10
 *  @author: Philip Gust
 */

#ifndef HTTP_UTIL_H_
#define HTTP_UTIL_H_

/**
 * Reads line of request from request stream and trims trailing CRLF.
 *
 * @param istream the socket input stream
 * @param buf the buffer to read into
 * @param len the length of the buffer
 * @return the buffer point of line read, else NULL
 */
char* readRequestLine(FILE *istream, char buf[], int len);

/**
 * Send status and fixed properties to response output stream.
 *
 * @param status the response status
 * @param statusMsg the response message
 * @param responseCharset the response charset
 * @throws IOException if error occurs
 */
void sendResponseStatus(FILE *ostream, int status, const char* statusMsg);

/**
 * Send property to response output stream.
 *
 * @param ostream the output socket stream
 * @param propName property name
 * @param propVal property value;
 */
void sendResponseProperty(FILE *ostream, char name[], char value[]);

/**
 * Send end of response properties to response output stream.
 *
 * @param ostream the output socket stream
 * @param propName property name
 * @param propVal property value;
 */
void endResponseProperties(FILE *ostream);

/**
 * Copy bytes from input stream to output stream
 * @param istream the input stream
 * @param ostream the output stream
 * @param nbytes the number of bytes to send
 */
void sendResponseBytes(FILE *istream, FILE *ostream, unsigned long nbytes);

/**
 * Set error response and error page to the response output stream.
 *
 * @param ostream the output socket stream
 * @param status the response status
 * @param statusMsg the response message
 * @param responseHeaders the response headers
 */
void sendErrorResponse(FILE* ostream, int responseCode, const char* responseStr);

/**
 * Resolves server URI to file system path.
 * @param uri the request URI
 * @param fspath the file system path
 */
void resolveUri(const char* uri, char* fspath);

/**
 * Get content type of file path.
 *
 * @param filePath the file path
 * @param contentType the content type
 */
void getContentType(char filePath[], char contentType[]);


#endif /* HTTP_UTIL_H_ */
