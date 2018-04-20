#include <fnet/socket.h>
#include <stdio.h>

int main()
{
    fnet_socket_init();

    fnet_address_t addr;
    fnet_str2addr("127.0.0.1:10500", &addr);

    fnet_socket_t cli = fnet_socket_create(FNET_SOCK_DGRAM);

    char buf[] = "ololo 12345";
    fnet_socket_sendto(cli, buf, sizeof buf, &addr);

    fnet_socket_close(cli);
    fnet_socket_uninit();
    return 0;
}
