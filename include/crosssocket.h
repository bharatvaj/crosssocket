#ifndef _XS_H
#define _XS_H "XS"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__) || defined(__APPLE__)
#if defined(__linux__) && defined(kernel_version_2_4)
#include <sys/sendfile.h>
#endif
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
typedef int xs_SOCKET;
#elif _WIN32
#include <winsock2.h>
typedef short ssize_t;
typedef int socklen_t;
#define xs_SOCKET SOCKET
#define xs_ERROR INVALID_SOCKET
#else
#error OS not supported
#endif

#ifndef xs_ERROR
#define xs_ERROR -1
#endif

/*
 * Cleans up os specific libraries
 */
static inline int xs_clean()
{
#ifdef _WIN32
		WSACleanup();
#endif
		return 0;
}

/*
 * Loads operating system specific libraries
 */
static inline int xs_init()
{
#ifdef _WIN32
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
				return 1;
		}

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
				xs_clean();
				return -1;
		}
#endif
		return 0;
}

static inline xs_SOCKET xs_socket(int af, int type, int protocol) {
 return socket(af, type, protocol);
}

static inline int xs_bind(xs_SOCKET socket, const struct sockaddr *address, socklen_t address_len) {
	return bind(socket, address, address_len);
}

static inline int xs_connect(xs_SOCKET socket, const struct sockaddr *address, socklen_t address_len) {
	return connect(socket, address, address_len);
}

static inline xs_SOCKET xs_accept(xs_SOCKET socket, struct sockaddr *address, socklen_t *address_len) {
 return accept(socket, address, address_len);
}

static inline int xs_send(xs_SOCKET sock, const char *buffer, int length, int flags) {
 return send(sock, buffer, length, flags);

}
static inline int xs_recv(xs_SOCKET sock, char *buffer, int length, int flags) {
 return recv(sock, buffer, length, flags);
}

static inline int xs_close(xs_SOCKET sock) {
 #if defined(_WIN32)
		 return closesocket(sock);
 #else
		 return close(sock);
 #endif
}

#ifdef __cplusplus
}
#endif
#endif
