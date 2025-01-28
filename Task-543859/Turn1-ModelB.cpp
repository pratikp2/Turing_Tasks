#include <stdio.h>
#include <stdlib.h>

enum Protocol {
    TCP = 6,
    UDP = 17,
    ICMP = 1
};

int handle_TCP_packet(char *payload, int payload_len) {
    printf("Handling TCP packet.\n");
    // TCP-specific packet processing logic here
    return 0;
}

int handle_UDP_packet(char *payload, int payload_len) {
    printf("Handling UDP packet.\n");
    // UDP-specific packet processing logic here
    return 0;
}

int handle_ICMP_packet(char *payload, int payload_len) {
    printf("Handling ICMP packet.\n");
    // ICMP-specific packet processing logic here
    return 0;
}

int main() {
    enum Protocol protocol;
    char payload[] = "Example network payload";  // Replace this with actual packet payload
    int payload_len = sizeof(payload);

    protocol = TCP; // Set the protocol for demonstration

    switch (protocol) {
        case TCP:
            handle_TCP_packet(payload, payload_len);
            break;
        case UDP:
            handle_UDP_packet(payload, payload_len);
            break;
        case ICMP:
            handle_ICMP_packet(payload, payload_len);
            break;
        default:
            fprintf(stderr, "Invalid protocol: %d\n", protocol);
            return 1;
    }

    return 0;
}
