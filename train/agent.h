#include "macro.h"

class agent {
public:
    agent(const V<u16>& masks, float a);
    ~agent();
    void save(str filepath);
    int choose_action(vi& state);
    void learn(vi& afterstate, vi& nextstate);
private:
    int MAX_P2 = 15;
    int NUM_TPL;
    float ALPHA;
    MAT<float> LUTS;
    MAT<int> LUT_CONFIG;
    int key(vi& state, int i);
    float evaluate(vi& state, int action);
    int move(vi& state, vi& afterstate, int action);
    float v(vi& state, float delta = 0);
};