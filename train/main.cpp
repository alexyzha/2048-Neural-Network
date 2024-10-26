#include "game.h"

int main(int argc, char* argv[]) {
    game G(0.025,"outfile.txt");
    F0R(i,10000)
        G.run();
    G.diagnostic();
    return 0;
}