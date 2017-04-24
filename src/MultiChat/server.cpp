#include "unp.h"


bool isEndOfMessage();

bool shouldTerminateConnection();

char line[BUFFER_SIZE];

int main() {
    struct sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        error("ERROR opening socket");

    int yes = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        error("ERROR reusing socket");
    }

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        error("ERROR on binding");
    }

    listen(serverSocket, 5);
    cout << "=> Waiting for clients " << endl;
    cout << "=> MAX = 5 clients" << endl;

    int pid;
    while (1) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket < 0) {
            error("ERROR on accept");
        }

        pid = fork();
        if (pid < 0) {
            error("ERROR in new process creation");
        }
        if (pid == 0) {
            close(serverSocket);

            write:
            while (1) {
                bzero(line, BUFFER_SIZE);
                cout << "server # ";
                cin.getline(line, BUFFER_SIZE);
                write(clientSocket, line, sizeof(line));

                if (isEndOfMessage()) goto read;
                else if (shouldTerminateConnection()) {
                    close(clientSocket);
                    exit(0);
                }
            }

            read:
            while (1) {
                cout << "=> wait for client " << endl;

                bzero(line, BUFFER_SIZE);
                read(clientSocket, line, sizeof(line));
                if (isEndOfMessage()) goto write;
                else if (shouldTerminateConnection()) {
                    close(clientSocket);
                    exit(0);
                }
                cout << "client # " << line << endl;
            }

        } else {
            close(clientSocket);
        }
    }

}

bool shouldTerminateConnection() { return line[0] == 'x'; }

bool isEndOfMessage() { return line[0] == '#'; }

