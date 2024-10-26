#include "game.h"

game::game(float a, str file) : player(new agent(TP_MASKS,a)), savefile(file) {}

game::~game() {
    if(!savefile.empty())
        player->save(savefile);
    delete player;
}

void game::run(bool vis, bool train) {
    cur_board.assign(cur_board.size(),0);
    make_tile(cur_board,2);
    CUR_SCORE = 0;
    bool running = 1;
    while(running) {
        //  Visualize board
        if(vis)
            print(cur_board);
        int action = player->choose_action(cur_board);
        //  Terminal state
        if(action == -1) {
            running = 0;
            break;
        }
        CUR_SCORE += move(action);
        //  Learn
        if(train) {
            vi afterstate = vi(16);
            copy(cur_board,afterstate);
            make_tile(cur_board);
            player->learn(afterstate,cur_board);
        } else 
            make_tile(cur_board);
    }
    MAX_SCORE = std::max(MAX_SCORE,CUR_SCORE);
    each(i,cur_board)
        MAX_TILE = std::max(MAX_TILE,i);
}

void game::make_tile(vi& board, int ct) {
    if(!can_place(board))
        return;
    int index = rand() % 16;
    while(board[index])
        index = rand() % 16;
    board[index] = tile_val();
}

void game::print(vi& board) {
    std::cout << std::endl;
    F0R(i,4) {
        F0R(j,4)
            std::cout << std::setw(4) << board[i*4+j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void game::diagnostic() {
    std::cout << "#==================#" << std::endl;
    std::cout << "Max score: " << MAX_SCORE << std::endl;
    std::cout << "Max tile: " << MAX_TILE << std::endl;
    std::cout << "#==================#" << std::endl;
}

int game::tile_val() {
    int p = rand() % 100 + 1;
    return p > 90 ? 4 : 2;
}

int game::move(int dir) {
    int score = 0;
    F0R(i,4) {
        vi line;
        F0R(j,4) {
            int index = BASE[dir][i] + j*DIR[dir];
            //  Skip 0s
            if(!cur_board[index])
                continue;
            //  Combine and set bitflag
            if(!line.empty() && line.back() == cur_board[index] && !(line.back()&MASK_ON))
                line.back() = ((cur_board[index]<<1)|MASK_ON),
                score += (cur_board[index]<<1);
            //  No combine
            else
                line.push_back(cur_board[index]);
        }
        //  Merge in place
        F0R(j,4) {
            int index = BASE[dir][i] + j*DIR[dir];
            cur_board[index] = j < line.size() ? (line[j]&MASK_OFF) : 0;
        }
    }
    return score;
}

bool game::can_place(vi& board) {
    each(i,board)
        if(!i)
            return 1;
    return 0;
}
