#include <vector>
#include <inttypes.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>

#ifndef ALY
#define ALY
//  Typedef
    using ll = long long;
    using ull = unsigned long long;
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using in8 = uint8_t;
    using in16 = uint16_t;
    using in32 = uint32_t;
    using in64 = uint64_t;
    using db = long double;
    using str = std::string;
//  Vecs
    #define vcA template<class A>
    vcA using V = std::vector<A>;
    vcA using MAT = V<V<A>>;
    using vi = V<int>;
    using vb = V<bool>;
    using vl = V<ll>;
    using vd = V<db>;
    using vs = V<str>;
//  Loops
    #define FOR(i,a,b) for(int i=(a);i<(b);++i)
    #define F0R(i,a) FOR(i,0,a)
    #define ROF(i,a,b) for(int i=(b)-1;i>=(a);--i)
    #define R0F(i,a) ROF(i,0,a)
    #define xtime(a) F0R(_,a)
    #define each(a,x) for(auto&a:x)
//  Bitmax & mog
    constexpr int pct(int x) { return __builtin_popcount(x); }
    constexpr int ctz(int x) { return __builtin_ctz(x); }   //  Count trailing zero
    constexpr int clz(int x) { return __builtin_clz(x); }   //  Count leading zero
//  Prints
    vcA void printvec(V<A>&a) { each(v,a) { std::cout << v << ' '; } std::cout << std::endl; }
    template<typename C>
    void meow(C num) {
        for(int bits=sizeof(num)*8;bits--;num>>=1) std::cout << !!(num&1);
        std::cout << std::endl;
    }
#endif

#ifndef DIRECTIONS
#define DIRECTIONS
    const vi DIR = {
        4,                  //  Starting up going down
        -1,                 //  Starting right going left
        -4,                 //  Starting down going up
        1                   //  Starting left going right
    };
    const MAT<int> BASE = {
        {0,1,2,3},          //  Merge up
        {3,7,11,15},        //  Merge right
        {12,13,14,15},      //  Merge down
        {0,4,8,12}          //  Merge left
    };
    const int MASK_ON = 0x80000000;
    const int MASK_OFF = 0x7FFFFFFF;
#endif

#ifndef HELPERS
#define HELPERS
    inline bool is_equal(vi& a, vi&b) {
        assert(a.size() == b.size());
        F0R(i,a.size())
            if(a[i] != b[i])
                return 0;
        return 1;
    }

    inline void copy(vi& src, vi& dest) {
        assert(src.size() == dest.size());
        F0R(i,src.size())
            dest[i] = src[i];
    }
#endif

#ifndef TUPLE_MASKS
#define TUPLE_MASKS
    const V<u16> TP_MASKS {
        //  Horizontal
        0b1111000000000000,
        0b0000111100000000,
        0b0000000011110000,
        0b0000000000001111,
        //  Vertical
        0b1000100010001000,
        0b0100010001000100,
        0b0010001000100010,
        0b0001000100010001,
        //  Squares
        0b1100110000000000,
        0b0110011000000000,
        0b0011001100000000,
        0b0000110011000000,
        0b0000011001100000,
        0b0000001100110000,
        0b0000000011001100,
        0b0000000001100110,
        0b0000000000110011
    };
#endif