// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description: 
#include "Center.h"

namespace edward {


std::ostream& operator<< (std::ostream& os, const Center& center) {
    os << center.C_;
    return os;
}

}