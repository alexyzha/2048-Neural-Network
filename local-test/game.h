#include "agent.h"

class game {
public:
    game(str file = "");
    ~game();
    void run(bool vis = 1);
    void diagnostic();
private:
    int RUNS = 0;
    int MAX_SCORE = 0;
    int CUR_SCORE = 0;
    int MAX_TILE = 0;
    int WINS = 0;
    float AVERAGE_SCORE = 0.0f;
    vi cur_board;
    agent* player;
    void make_tile(vi& board, int ct = 1);
    void print(vi& board);
    int tile_val();
    int move(int dir);
    bool can_place(vi& board);
};