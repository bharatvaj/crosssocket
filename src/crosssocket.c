#include <crosssocket.h>

#ifdef _WIN32
#include <windef.h>
#endif

#include <clog/clog.h>

//TODO
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

//TODO
int xs_clean()
{
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}

xs_SOCKET xs_socket(int af, int type, int protocol)
{
    return socket(af, type, protocol);
}

//TODO
int xs_send(xs_SOCKET sock, void *buffer, int bufflen, int flags)
{
    return send(sock, buffer, bufflen, flags);
}

//TODO
int xs_recv(xs_SOCKET sock, void *buffer, int bufflen, int flags)
{
    return recv(sock, buffer, bufflen, flags);
}

//TODO
int xs_close(xs_SOCKET sockfd)
{
#if defined(_WIN32)
    return closesocket(sockfd);
#else
    return close(sockfd);
#endif
}
