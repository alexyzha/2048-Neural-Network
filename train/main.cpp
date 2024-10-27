#include "game.h"

int main(int argc, char* argv[]) {
    game G(0.025,"outfile.txt");
    F0R(i,500000)
        G.run(i);
    G.diagnostic();
    return 0;
}