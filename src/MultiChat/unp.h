#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/un.h>
#include<string.h>
#include<sys/uio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>

using namespace std;

const int BUFFER_SIZE = 256;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}