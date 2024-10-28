#include "game.h"

game::game(str file) : player(new agent(file)) {}

game::~game() {
    delete player;
}

void game::run(bool vis) {
    ++RUNS;
    cur_board = vi(16,0);
    make_tile(cur_board,2);
    CUR_SCORE = 0;
    bool running = 1;
    while(running) {
        //  Visualize board
        if(vis) {
            print(cur_board);
            std::cout << RUNS << std::endl;
        }
        int action = player->choose_action(cur_board);
        //  Terminal state
        if(action == -1) {
            running = 0;
            break;
        }
        CUR_SCORE += move(action);
        make_tile(cur_board);
    }
    //  Ensure
    print(cur_board);
    std::cout << RUNS << std::endl;
    MAX_SCORE = std::max(MAX_SCORE,CUR_SCORE);
    AVERAGE_SCORE += CUR_SCORE;
    bool win = 0;
    each(i,cur_board) {
        MAX_TILE = std::max(MAX_TILE,i);
        if(i >= 2048)
            win = 1;
    }
    WINS += win;
}

void game::make_tile(vi& board, int ct) {
    F0R(_,ct) {
        if(!can_place(board))
            return;
        int index = rand() % 16;
        while(board[index])
            index = rand() % 16;
        board[index] = tile_val();
    }
}

void game::print(vi& board) {
    std::cout << std::endl;
    F0R(i,4) {
        F0R(j,4)
            std::cout << std::setw(5) << board[i*4+j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void game::diagnostic() {
    std::cout << "#==================#" << std::endl;
    std::cout << "Max score: " << MAX_SCORE << std::endl;
    std::cout << "Average score: " << AVERAGE_SCORE/RUNS << std::endl;
    std::cout << "Max tile: " << MAX_TILE << std::endl;
    std::cout << "Win rate: " << (WINS*100.0f/RUNS) << '%' << std::endl;
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
