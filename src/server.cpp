#include "unp.h"

int servCount = 0;
int main(int argc, char **argv) {

    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT_NUM);
    bind(listenfd, (sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    while (1) {
        cout << "waiting for clients " << endl;
        connfd = accept(listenfd, (sockaddr *) NULL, NULL);
        cout << "Client "" connected << sending payload" << endl;
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}
