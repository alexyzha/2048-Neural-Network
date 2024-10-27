#include "agent.h"

agent::agent(const V<u16>& masks, float a) : ALPHA(a) {
    NUM_TPL = masks.size();
    LUTS = MAT<float>(NUM_TPL);
    LUT_CONFIG = MAT<int>(NUM_TPL);
    F0R(i,NUM_TPL) {
        int weights = std::pow(MAX_P2,4);
        LUTS[i] = V<float>(weights,0.0f);
        LUT_CONFIG[i] = V<int>(pct(masks[i]));
        int index = 0;
        //  Get tuple configs from bitmask
        F0R(j,16)
            if((1<<j)&masks[i])
                LUT_CONFIG[i][index++] = j;
    }
}

agent::~agent() {}

void agent::save(str filepath) {
    std::ofstream file(filepath);
    if(!file) {
        std::cerr << "Invalid file path" << std::endl;
        return;
    }
    //  Store each tuple
    F0R(i,NUM_TPL) {
        //  <tuple number> <tuple size> <tuple config>
        file << i << ' ' << LUTS[i].size() << ' ';
        for(auto&j:LUT_CONFIG[i])
            file << j << ' ';
        file << std::endl;
        //  <all tuple weights>
        for(auto&j:LUTS[i])
            file << j << std::endl;
    }
}

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

void agent::learn(vi& afterstate, vi& nextstate) {
    //  Get best action for s''
    int next_action = choose_action(nextstate);
    float v_nextafter = 0.0f;
    int r_next = 0;
    //  If legal action
    if(next_action != -1) {
        vi nextafter = vi(16);
        r_next = move(nextstate,nextafter,next_action);
        v_nextafter = v(nextafter);
    }
    //  Update
    float delta = r_next + v_nextafter - v(afterstate);
    v(afterstate,ALPHA * delta);
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

float agent::v(vi& state, float delta) {
    float ret = 0.0f;
    F0R(tuple,NUM_TPL) {
        int t_id = key(state,tuple);
        if(delta)
            LUTS[tuple][t_id] += delta;
        ret += LUTS[tuple][t_id];
    }
    //  Return mean E(score) of all tuples
    return ret/NUM_TPL;
}