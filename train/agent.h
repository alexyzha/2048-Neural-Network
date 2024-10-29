#include "macro.h"

class agent {
public:
    /*
     *  @param masks 16-bit bitmasks for tuple scope
     *  @param a learning rate
     */
    agent(const V<u16>& masks, float a);

    /*
     *  No special delete
     */
    ~agent();

    /*
     *  Saves all weights & tuple config to file at filepath
     */
    void save(str filepath);

    /* 
     *  Simulates all possible moves, picks one based on
     *  R(s,a) + V(s') and returns the move (range = [0,3])
     *  - returns -1 for terminal state
     */
    int choose_action(vi& state);

    /*
     *  Updates all weights during v(state) calculation
     *  - V(s') += alpha * delta
     *  - delta = R(s_next,a_next) + V(s_next') - V(s')
     */
    void learn(vi& afterstate, vi& nextstate);

private:
    int MAX_P2 = 15;
    int NUM_TPL;
    float ALPHA;
    MAT<float> LUTS;
    MAT<int> LUT_CONFIG;

    /*
     *  @param state any state
     *  @param i tuple index
     */
    int key(vi& state, int i);

    /*
     *  Returns R(s,a) + V(s') or -2 if invalid move
     */
    float evaluate(vi& state, int action);

    /*
     *  Returns R(s,a), stores s' in afterstate
     */
    int move(vi& state, vi& afterstate, int action);
    
    /*
     *  Updates weights when delta != 0
     *  Returns V(state)
     */
    float v(vi& state, float delta = 0);

};