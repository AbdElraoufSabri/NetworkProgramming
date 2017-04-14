#include "unp.h"


using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main (){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
        error("ERROR opening socket");

    struct sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    char serverResponse[256];
    bzero(serverResponse,256);

    int n;

    if (connect(clientSocket, (struct sockaddr *) & serverAddress, sizeof(serverAddress)) < 0){
        error("Error making connection\n\n");
    }

    while((n = read(clientSocket,serverResponse,sizeof(serverResponse)) > 0))
        cout << serverResponse;

    if(n < 0)
    {
        error("error receiving message");
        return 1;
    }

    close(clientSocket);
    return 0;
}