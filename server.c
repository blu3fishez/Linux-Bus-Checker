// the program that uses the socket
// date : 2020-12-19-2am
// description : server process for sending current time.
// This Code refered to Chapter 11. socket, Timeclinet.c

#include"basiclib.h"
#define PORTNUM 5500
#define HOSTLEN 256
#define DebugLog(msg) {perror(msg); exit(1);}

char* ctime();

int main(int ac, char* av[]){
    struct sockaddr_in saddr;
    struct hostent *hostptr;
    char hostname[HOSTLEN]; // address for server
    int sock_id, sock_fd;
    FILE* sock_fp;
    time_t curtime; // current time

    // socket procedure
    // 1. ask kernel for a socket
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id == -1)
        DebugLog("asking to kernal for a socket");
    // 2. bind addres to socket
    bzero((void*)&saddr, sizeof(saddr));
    gethostname(hostname, HOSTLEN);
    hostptr = gethostbyname(hostname);
    bcopy((void*)hostptr->h_addr, (void*)&saddr.sin_addr, hostptr->h_length);

    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if(bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0)
        DebugLog("binding error");
    // 3. allow incoming calls with Qsize =  1 on socket
    if(listen(sock_id, 1) != 0)
        DebugLog("listening PORT");

    while(1){
        sock_fd = accept(sock_id, NULL, NULL);
        if(sock_fd == -1)
            DebugLog("Accepting Socket...");
        sock_fp = fdopen(sock_fd, "w");
        if(sock_fp == NULL)
            DebugLog("fdopening");
        curtime = time(NULL);

        fprintf(sock_fp, "The Current Time : ");
        fprintf(sock_fp, "%s\n", ctime(&curtime));
        fclose(sock_fp);
    }
}