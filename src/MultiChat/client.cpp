#include "unp.h"

bool isEndOfMessage();

bool shouldTerminateConnection();

char line[BUFFER_SIZE];

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
        error("ERROR opening socket");

    struct sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;


    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        error("Error making connection");
    }

        read:
        while (1) {
            cout << "=> wait for server " << endl;
            bzero(line, BUFFER_SIZE);
            read(clientSocket, line, sizeof(line));
            if (isEndOfMessage()) goto write;
            else if (shouldTerminateConnection()) {
                close(clientSocket);
                exit(0);
            }
            cout << "server # " << line << endl;
        }

        write:
        while (1) {
            bzero(line, BUFFER_SIZE);
            cout << "client # ";
            cin.getline(line, BUFFER_SIZE);
            write(clientSocket, line, sizeof(line));
            if (isEndOfMessage()) goto read;
            else if (shouldTerminateConnection()) {
                close(clientSocket);
                exit(0);
            }
        }

}

bool shouldTerminateConnection() { return line[0] == 'x'; }

bool isEndOfMessage() { return line[0] == '#'; }

