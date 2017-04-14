#include "unp.h"


using namespace std;

int main() {
    struct sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        cout << "ERROR opening socket" << endl;

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cout << "ERROR on binding" << endl;
    }

    listen(serverSocket, 5);
    cout << "waiting for clients " << endl;
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket < 0) {
        cout << "ERROR on accept" << endl;
    }

    FILE *htmlFile = fopen("index.html", "r");

    char line[256];
    bzero(line, 256);
    std::string tmpString;

    while (fgets(line, sizeof(line), htmlFile)) {
        write(clientSocket, line, 256);

        bzero(line, 256);
    }

    fclose(htmlFile);
    close(clientSocket);
    close(serverSocket);
    return 0;
}