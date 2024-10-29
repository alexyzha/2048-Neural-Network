#include "macro.h"

class agent {
public:
    agent(str path);
    ~agent();
    int choose_action(vi& state);
private:
    int MAX_P2 = 15;
    int NUM_TPL;
    MAT<float> LUTS;
    MAT<int> LUT_CONFIG;
    int key(vi& state, int i);
    float evaluate(vi& state, int action);
    int move(vi& state, vi& afterstate, int action);
    float v(vi& state);
};

/*
 *  For all code comments refer to ../../train
 */