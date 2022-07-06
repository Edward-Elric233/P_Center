// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#ifndef P_CENTER_UTILS_H
#define P_CENTER_UTILS_H

#include <iostream>
#include <random>

namespace edward {

constexpr int INF = 0x3f3f3f3f;

inline void print() {
    std::cout << "\n";
}
template<typename T, typename... Args>
void print(T&& first, Args&&... args) {
    std::cout << first << " ";
    print(std::forward<Args>(args)...);
}

class Random {
public:
    // random number generator.
    static std::mt19937 pseudoRandNumGen;
    static void initRand(int seed) { pseudoRandNumGen = std::mt19937(seed); }
    static int fastRand(int lb, int ub) { return (pseudoRandNumGen() % (ub - lb)) + lb; }
    static int fastRand(int ub) { return pseudoRandNumGen() % ub; }
    static int rand(int lb, int ub) { return std::uniform_int_distribution<int>(lb, ub - 1)(pseudoRandNumGen); }
    static int rand(int ub) { return std::uniform_int_distribution<int>(0, ub - 1)(pseudoRandNumGen); }
};



}

#endif //P_CENTER_UTILS_H
