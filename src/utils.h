// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#ifndef P_CENTER_UTILS_H
#define P_CENTER_UTILS_H

#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

namespace edward {

constexpr int INF = 0x3f3f3f3f;

extern std::ofstream ofs;

inline void print() {
//    std::cout << "\n";
    ofs << "\n";
}
template<typename T, typename... Args>
void print(T&& first, Args&&... args) {
//    std::cout << first << " ";
    ofs << first << " ";
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

class Timer {
    std::chrono::time_point<std::chrono::system_clock> timePoint_;
public:
    Timer(): timePoint_(std::chrono::system_clock::now()) {}
    Timer(const Timer&) = delete;
    ~Timer() = default;
    void operator() (const std::string& msg) {
        auto duration = std::chrono::system_clock::now() - timePoint_;
        print(msg, static_cast<double>(duration.count()) / decltype(duration)::period::den, "s");
    }
};

namespace param {
    extern int n;
}

}

#endif //P_CENTER_UTILS_H
