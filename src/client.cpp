#include "unp.h"

int main(int argc, char** argv)
{
    int sockfd,n;
    struct sockaddr_in servaddr;
    char recvline[MAXLINE+1];
    if(argc!=2)
    {
        cout<<("command argument error")<<endl;
        exit(1);
    }
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        cout<<("socket error")<<endl;
        exit(1);
    }
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT_NUM);
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
    {
        cout<<("inet_pton error")<<endl;
        exit(1);
    }

    if(connect(sockfd,(sockaddr *) &servaddr,sizeof(servaddr))<0)
    {
        cout<<("socket creation  error")<<endl;
        exit(1);
    }
    while((n=read(sockfd,recvline,MAXLINE))>0)
    {
        recvline[n]=0;
        if(fputs(recvline,stdout)==EOF)
        {
            cout<<("fput error")<<endl;
            exit(1);
        }
    }
    if(n<0)
    {
        cout<<("reading error")<<endl;
        exit(1);
    }
    exit(0);
    return 0;
}