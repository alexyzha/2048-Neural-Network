#include "agent.h"

class game {
public:
    game(float a, str file = "");
    ~game();
    void run(bool vis = 1, bool train = 1);
private:
    int MAX_SCORE = 0;
    int CUR_SCORE = 0;
    int MAX_TILE = 0;
    str savefile;
    vi cur_board;
    agent* player;
    void make_tile(vi& board, int ct = 1);
    void print(vi& board);
    void diagnostic();
    int tile_val();
    int move(int dir);
    bool can_place(vi& board);
};