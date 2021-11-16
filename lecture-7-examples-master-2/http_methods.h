/*
 * http_methods.h
 *
 * Functions that implement HTTP methods, including GET.
 *
 *  @since 2019-04-10
 *  @author: Philip Gust
 */

#ifndef HTTP_METHODS_H_
#define HTTP_METHODS_H_

#include <stdio.h>

/**
 * Handle GET request.
 *
 * @param the socket stream
 * @param uri the request URI
 */
void do_get(FILE *stream, const char uri[]);

#endif /* HTTP_METHODS_H_ */
