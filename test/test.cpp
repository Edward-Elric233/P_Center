// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#include "test.h"
#include "Set.h"
#include "utils.h"
#include "RandomSet.h"

namespace edward {

void test_Set() {
    /*
    edward::Set a({1,2}), b({3,4,5});
    //a.insert(4);

    print("a.size():", a.size());
    print("a & b:", a & b);
    print("a | b:", a | b);
    //print("a &= b:", a &= b);
    print("a |= b:", a |= b);
    */
}

void test_RandomSet() {
    RandomSet randomSet(10);
    randomSet.insert(0);
    randomSet.insert(1);
    randomSet.insert(2);
    print(randomSet);
    randomSet.erase(1);
    print(randomSet);
    print(randomSet.size());
    randomSet.erase(2);
    randomSet.erase(0);
    randomSet.insert(9);
    print(randomSet);
}

void test_Set_efficiency() {
    constexpr int MAXN = 1000000;
    Timer timer_Set;
    edward::Set set;
    for (int i = 0; i < MAXN; ++i) {
        set.insert(i);
    }
    for (int i = 0; i < MAXN; i += 2) {
        set.erase(i);
    }
    for (int i = 0; i < MAXN; i += 2) {
        set.insert(i);
    }
    print("Set.size() =", set.size());
    timer_Set("Set:");
    Timer timer_RandomSet;
    edward::RandomSet randomSet(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        randomSet.insert(i);
    }
    for (int i = 0; i < MAXN; i += 2) {
        randomSet.erase(i);
    }
    for (int i = 0; i < MAXN; i += 2) {
        randomSet.insert(i);
    }
    print("RandomSet.size() =", randomSet.size());
    timer_RandomSet("RandomSet:");
}

void test_unpack() {
    auto &&[begin1, end1] = std::make_pair(1, 1);
}

void test_Vector() {
    print("test_Vector", int());
}

}

#include <bits/stdc++.h>
using namespace std;
void test() {
    unordered_map<int, string>::iterator iter;
    auto pr = *iter;
}