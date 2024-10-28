#include "game.h"

int main(int argc, char* argv[]) {
    game G("bot/infile.txt");
    F0R(i,1000)
        G.run(0);
    G.diagnostic();
    return 0;
}