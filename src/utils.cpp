// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#include "utils.h"

namespace edward {

std::mt19937 Random::pseudoRandNumGen;

std::ofstream ofs("..\\test\\debug.txt", std::ofstream::app);

namespace param {
    int n;
}

}