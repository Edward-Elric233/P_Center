// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#include "test.h"
#include "Set.h"
#include "utils.h"

namespace edward {

void test_Set() {
    edward::Set a({1,2}), b({3,4,5});
    //a.insert(4);

    print("a.size():", a.size());
    print("a & b:", a & b);
    print("a | b:", a | b);
    //print("a &= b:", a &= b);
    print("a |= b:", a |= b);
}

}
