// the child process of system.c
// the client process for getting current time
// process is made by fork.
// date 2020-12-1-4:13am

#include"basiclib.h"
#define DebugLog(msg) {perror(msg); exit(1);}

int main(int ac, char* av[]){
    struct sockaddr_in servadd;
    struct hostent *hp;
    int sock_id, sock_fd;
    char message[BUFSIZ];
    int messlen;
    // socket client procedure
    // 1. get a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id == -1)
        DebugLog("Getting Socket");

    // 2. connect to server
    bzero(&servadd, sizeof(servadd));
    hp = gethostbyname(av[1]); // av[1] is host's ip. av[1] should be localhost for testing
    if(hp == NULL) DebugLog("Getting HostPointe");
    bcopy(hp->h_addr, (struct sockaddr*)&servadd.sin_addr, hp->h_length);
    servadd.sin_port = htons(atoi(av[2]));
    servadd.sin_family = AF_INET;

    if(connect(sock_id, (struct sockaddr*)&servadd, sizeof(servadd)) != 0)
        DebugLog("connection");
    // 3. transter data from server, then hangup
    messlen = read(sock_id, message, BUFSIZ);
    if(messlen == -1) DebugLog("Reading From Server");
    if(write(1, message, messlen) != messlen)
        DebugLog("Writing From Server");
    close(sock_id);
}
