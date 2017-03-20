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
#define MAXLINE 4096
#define LISTENQ 1024
#define PORT_NUM 1234
using namespace std;
void err_quit(const char *x)
{
	printf("%s",x);
	exit(-1);
}