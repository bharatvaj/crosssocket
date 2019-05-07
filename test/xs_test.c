#include <stdio.h>
#include <crosssocket.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#define _D_PORT 3500

static const char *TAG = "TEST";

xs_SOCKET sock;

int test_server(int port){
  return -1;
}

int main(int argc, char *argv[])
{
  int status = -1;
  if (argc < 2)
  {
    return -1;
  }
  xs_init();
  if (strcmp(argv[1], "server") == 0)
  {
    status &= test_server(_D_PORT);
  }
  else
  {
    printf("Unknown parameter\n");
    return -1;
  }
  // xs_close(sock);
  xs_clean();
  return status;
}
