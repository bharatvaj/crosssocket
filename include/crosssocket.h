#ifndef _XS
#define _XS "XS"
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
typedef int SOCKET;
#define SOCKET_ERROR -1
#elif _WIN32
//#include <windows.h>
//#include <ws2tcpip.h>
#include <winsock2.h>
#include <Windows.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
	typedef short ssize_t;
	typedef int socklen_t;
#else
	typedef int xs_SOCKET;
#error OS not supported
#endif

#define XS_BUFFER_SIZE 256
#define XS_CON_MAX_ATTEMPTS 5
#define XS_SERV_BACKLOG 10

typedef SOCKET xs_SOCKET;
/*
 * Loads operating system specific libraries
 */
int xs_init()
{
#ifdef _WIN32
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
				log_fat(_XS, "WSAStartup failed with error: %d\n", err);
				return 1;
		}

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
				log_fat(_XS, "Could not find Winsock.dll with version 2.2, please install one");
				xs_clean();
				return -1;
		}
#endif
		return 0;
}

int xs_clean()
{
#ifdef _WIN32
		WSACleanup();
#endif
		return 0;
}


inline xs_SOCKET xs_socket(int af, int type, int protocol) {
 return socket(af, type, protocol);
}

int bind(xs_SOCKET socket, const struct sockaddr *address, socklen_t address_len) {
	return bind(socket, address, address_len);
}

int connect(xs_SOCKET socket, const struct sockaddr *address, socklen_t address_len) {
	return connect(socket, address, address_len);
}

inline xs_SOCKET xs_accept(xs_SOCKET socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
 return accept(socket, address, address_len);
}

inline int xs_send(xs_SOCKET sock, const void *buffer, int length, int flags) {
 return send(sock, buffer, length, flags);

}
inline int xs_recv(xs_SOCKET sock, void *buffer, int length, int flags) {
 return recv(sock, buffer, length, flags);
}

inline int xs_close(xs_SOCKET sock) {
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
