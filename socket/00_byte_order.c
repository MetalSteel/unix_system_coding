#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    uint32_t i = 0x12345678;
    unsigned char *ptr = (char*)&i;
    printf("%0x %0x %0x %0x\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    // htonl: host to network (long type -> long type) 
    // htons: host to network (short type -> short type)
    // ntohl: network to host (long type -> long type)
    // ntohs: network to host (short type -> short type)

    // host to network byte order
    i = htonl(i);
    ptr = (char*)&i;
    printf("%0x %0x %0x %0x\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    i = ntohl(i);
    ptr = (char*)&i;
    printf("%0x %0x %0x %0x\n", ptr[0], ptr[1], ptr[2], ptr[3]);
    
    return EXIT_SUCCESS;
}
