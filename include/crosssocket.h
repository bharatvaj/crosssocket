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
inline int xs_init();

/*
 * Frees up memory
 */
inline int xs_close(xs_SOCKET);

inline int xs_socket(int, int, int);
inline int xs_send(xs_SOCKET sock, void *buffer, int buf_len, int flags);
inline int xs_recv(xs_SOCKET sock, void *buffer, int buf_len, int flags);

#ifdef __cplusplus
}
#endif
#endif
