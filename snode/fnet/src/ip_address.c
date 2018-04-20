#include "ip_address.h"
#include <fcommon/limits.h>
#include <fcommon/log.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>

bool fnet_str2addr(char const *str, fnet_address_t *addr)
{
    if (!str || !addr)
    {
        FLOG_ERR("Invalid argument");
        return false;
    }

    size_t const len = strlen(str);
    if (len > FMAX_ADDR)
    {
        FLOG_ERR("Address length is too long");
        return false;
    }

    memset(addr, 0, sizeof *addr);

    char host[len + 1];
    strncpy(host, str, len + 1);

    char *port = strrchr(host, ':');
    if (port) *(port++) = 0;

    struct addrinfo *result = 0;
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host, port, &hints, &result))
    {
        FLOG_ERR("getaddrinfo failed");
        return false;
    }

    bool ret = false;

    for(struct addrinfo *ptr = result; ptr; ptr = ptr->ai_next)
    {
        if (ptr->ai_family == AF_INET)
        {
            struct sockaddr_in *src_addr = (struct sockaddr_in*)ptr->ai_addr;
            struct sockaddr_in *dst_addr = (struct sockaddr_in*)addr;
            memcpy(dst_addr, src_addr, sizeof *src_addr);
            ret = true;
            break;
        }
        else if (!addr->ss_family && ptr->ai_family == AF_INET6)
        {
            struct sockaddr_in6 *src_addr = (struct sockaddr_in6*)ptr->ai_addr;
            struct sockaddr_in6 *dst_addr = (struct sockaddr_in6*)addr;
            memcpy(dst_addr, src_addr, sizeof *src_addr);
            ret = true;
        }
    }

    freeaddrinfo(result);

    return ret;
}

bool fnet_addr2str(fnet_address_t const *addr, char *str, unsigned len)
{
    if (!str || !addr || !len)
    {
        FLOG_ERR("Invalid argument");
        return false;
    }

    if (getnameinfo((struct sockaddr const *)addr, sizeof *addr, str, len, 0, 0, NI_NUMERICHOST | NI_NUMERICSERV) != 0)
        return false;

    unsigned addr_len = strlen(str);
    if (addr_len < len)
        snprintf(str + addr_len, len - addr_len, ":%u", ntohs(((struct sockaddr_in const *)addr)->sin_port));

    return true;
}
