#include "agent.h"

int main(int argc, char* argv[]) {
    //  No bot file
    if(argc != 2) {
        std::cerr << "./server [bot filepath]" << std::endl;
        return -1;
    }
    //  Initialize player
    agent* PLAYER = new agent(argv[1]);
    //  Initialize server socket & addr
    int SERVER_SOCKET = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in SERVER_ADDRESS;
    SERVER_ADDRESS.sin_family = AF_INET;
    SERVER_ADDRESS.sin_port = htons(8080);
    //  Listen for any inaddr
    SERVER_ADDRESS.sin_addr.s_addr = INADDR_ANY;
    //  Bind socket to server
    bind(SERVER_SOCKET,(struct sockaddr*)&SERVER_ADDRESS,sizeof(SERVER_ADDRESS));
    //  Listen on server socket
    listen(SERVER_SOCKET,5);
    //  Accept client connection
    int CLIENT_SOCKET = accept(SERVER_SOCKET,nullptr,nullptr);
    //  Get data from client
    vi board = vi(16,0);
    const char CHAR_DIR[5] = {'e','w','d','s','a'};
    bool playing = 1;
    while(playing) {
        //  Log2scale @py before py->cpp
        char MESSAGE[16];
        //  Receive message from client
        recv(CLIENT_SOCKET,MESSAGE,sizeof(MESSAGE),0);
        //  Convert from log2scale to regular
        F0R(i,16)
            board[i] = MESSAGE[i] ? static_cast<int>(1<<MESSAGE[i]) : 0;
        int MOVE = PLAYER->choose_action(board)+1;
        //  Send message back, ' ' = terminal
        const char RESPONSE[1] = {CHAR_DIR[MOVE]};
        send(CLIENT_SOCKET,RESPONSE,1,0);
        if(MOVE < 0)
            playing = 0;
    }
    //  Close server socket
    close(CLIENT_SOCKET);
    close(SERVER_SOCKET);
    return 0;
}