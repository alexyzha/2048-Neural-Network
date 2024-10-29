#include "agent.h"

class game {
public:
    /*
     *  @param a learning rate
     *  @param file where bot will save to
     */
    game(float a, str file = "");
    
    /*
     *  Save and then delete bot
     */
    ~game();

    /*
     *  @param iter game number
     *  @param vis print all states?
     *  @param train train bot?
     */
    void run(int iter, bool vis = 1, bool train = 1);
    
    /*
     *  Print all game data (highest score, largest tile)
     */
    void diagnostic();

private:
    int MAX_SCORE = 0;
    int CUR_SCORE = 0;
    int MAX_TILE = 0;
    str savefile;
    vi cur_board;
    agent* player;

    /*
     *  Create a random tile if possible on board
     */
    void make_tile(vi& board, int ct = 1);
    
    /*
     *  Prints board
     */
    void print(vi& board);

    /*
     *  Generates random tile value
     *  - 90% 2
     *  - 10% 4
     */
    int tile_val();

    /*
     *  Move in direction dir
     */
    int move(int dir);

    /*
     *  Returns true if there is an empty tile
     */
    bool can_place(vi& board);
};