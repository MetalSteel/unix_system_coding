#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    // string ip address convert to network byte order
    uint32_t addr = inet_addr("192.168.0.100");
    printf("192.168.0.100 -> %u\n", htonl(addr));
    
    // string ip address convert to network byte order
    printf("192.168.0.100 -> %u\n", inet_network("192.168.0.100"));

    // host byte order convert to string ip address
    struct in_addr ip_addr;
    ip_addr.s_addr = addr;
    printf("%u -> %s\n", addr, inet_ntoa(ip_addr));
    
    return EXIT_SUCCESS;
}
