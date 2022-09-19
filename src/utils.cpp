// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#include "utils.h"

namespace edward {

std::mt19937 Random::pseudoRandNumGen;

#ifdef __WIN32__
    std::ofstream ofs("..\\test\\debug.txt");
#elif __linux__
    std::ofstream ofs("../test/debug.txt");
#endif

namespace param {
    int n;
}

}