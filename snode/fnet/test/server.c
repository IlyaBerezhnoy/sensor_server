#include <fnet/socket.h>
#include <stdio.h>

int main()
{
    fnet_socket_init();

    fnet_address_t srv_addr;
    fnet_str2addr("127.0.0.1:10500", &srv_addr);
    fnet_socket_t srv = fnet_socket_bind(FNET_SOCK_DGRAM, &srv_addr);

    char buf[65536];
    size_t read_len = 0;
    fnet_address_t addr;
    
    if (fnet_socket_recvfrom(srv, buf, sizeof buf, &read_len, &addr))
    {
        buf[read_len - 1] = 0;
        
        char cli_addr[128];
        fnet_addr2str(&addr, cli_addr, sizeof cli_addr);
        printf("Got: %s, from %s\n", buf, cli_addr);

        fnet_socket_sendto(srv, buf, read_len, &addr);
    }

    fnet_socket_close(srv);
    fnet_socket_uninit();
    return 0;
}
