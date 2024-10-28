#include "agent.h"

agent::agent(str path) {
    std::ifstream file(path);
    assert(file);
    int TPL_CONFIG_CT;
    file >> NUM_TPL >> TPL_CONFIG_CT;
    LUTS = MAT<float>(NUM_TPL,V<float>(std::pow(MAX_P2,TPL_CONFIG_CT)));
    LUT_CONFIG = MAT<int>(NUM_TPL,vi(TPL_CONFIG_CT));
    F0R(i,NUM_TPL) {
        int index, len;
        file >> index >> len;
        //  Get all tuple configs in order of save
        F0R(j,TPL_CONFIG_CT)
            file >> LUT_CONFIG[index][j];
        //  Get all LUT floats in order of save
        F0R(j,len)
            file >> LUTS[index][j];
    }
    file.close();
}

agent::~agent() {}

int agent::choose_action(vi& state) {
    int action = -1;
    float best = -1.0f;
    F0R(i,4) {
        float r = evaluate(state,i);
        if(r > best)
            action = i,
            best = r;
    }
    return action;
}

int agent::key(vi& state, int i) {
    int key = 0;
    int base = 1;
    each(tile,LUT_CONFIG[i]) {
        assert(log2(state[tile]) < MAX_P2);
        key += log2(state[tile])*base;
        base *= MAX_P2;
    }
    return key;
}

float agent::evaluate(vi& state, int action) {
    vi afterstate = vi(16); 
    int r = move(state,afterstate,action);
    //  If afterstate = state, then illegal move
    if(is_equal(state,afterstate))
        return -2.0f;
    //  Calculate reward from moving, get v(s')
    return r + v(afterstate);
}

int agent::move(vi& state, vi& afterstate, int action) {
    int score = 0;
    F0R(i,4) {
        vi line;
        F0R(j,4) {
            int index = BASE[action][i] + j*DIR[action];
            //  Skip 0s
            if(!state[index])
                continue;
            //  Combine and set bitflag
            if(!line.empty() && line.back() == state[index] && !(line.back()&MASK_ON))
                line.back() = ((state[index]<<1)|MASK_ON),
                score += (state[index]<<1);
            //  No combine
            else
                line.push_back(state[index]);
        }
        //  Populate afterstate
        F0R(j,4) {
            int index = BASE[action][i] + j*DIR[action];
            afterstate[index] = j < line.size() ? (line[j]&MASK_OFF) : 0;
        }
    }
    return score;
}

float agent::v(vi& state) {
    float ret = 0.0f;
    F0R(tuple,NUM_TPL) {
        int t_id = key(state,tuple);
        ret += LUTS[tuple][t_id];
    }
    //  Return mean E(score) of all tuples
    return ret/NUM_TPL;
}