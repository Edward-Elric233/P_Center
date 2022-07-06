// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description: 
#include "Element.h"

namespace edward {


std::ostream& operator<< (std::ostream& os, const Element& element) {
    os << element.B_;
    return os;
}

}