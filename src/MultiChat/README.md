# Multi chat application

uses `fork()`

## Download and run
1. open Terminal
2. `sudo apt-get install git`
3. `git clone https://github.com/AbdElraoufSabri/NetworkProgramming.git`
4. `cd NetworkProgramming/src/MultiChat`
5. `make`
6. `./server`
7. Right click and choose `Open Terminal`
8. `./client`

## Code notes

### 1 : Helper code
```c
bool isEndOfMessage();
bool shouldTerminateConnection();
char line[BUFFER_SIZE];
..
..
..
bool shouldTerminateConnection() { return line[0] == 'x'; }

bool isEndOfMessage() { return line[0] == '#'; }
```
### 2 : Read line of text
```c
cin.getline(line, BUFFER_SIZE);
```
reads into `line` from `cin` which comes from keyboard by default and reads BUFFER_SIZE chars

**BUFFER_SIZE** : is the number of chars to be read

### 3 : Reusing socket
```c
int yes = 1;
if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    error("ERROR reusing socket");
}
```
the call to `setsockopt` with `&yes` parameter tells the kernel to reuse the socket if it's already created.

### 4 : Fork the real MESS in the `server` code
```c
int pid;
while (1) {
    ...
    ...
    pid = fork();
    if (pid < 0) {
        error("ERROR in new process creation");
    }
    if (pid == 0) {
        close(serverSocket);
        ...
        ...
    } else {
        close(clientSocket);
    }
```
`fork()` creates a child process executing the same code as it's parent unless it was told to execute some other different code.

First, we defined a `pid` variable to store the status of the `fork()` call.

#### `fork()` status
**-1** : error happened while creating the child, may be the kernel don't allow that or the process doesn't have enough permissions.

**0** : this status indicates that we are in the _child_ process

**1** : this status indicates that we are in the _parent_ process

#### How to handle the fork ?
The server creates two different sockets. The `serverSocket` and a `clientSocket` for each new client.

**Here's a rule of thumb** The server does't need the `clientSocket` it just deals with `serverSocket` so in the _parent_ process we need to close `clientSocket`. And like that, the child process doesn't need the `serverSocket` it just deals with `clientSocket` so in the _child_ process we need to close `serverSocket`.

## That's it

Thanks **Eng.Elhosseiny**
