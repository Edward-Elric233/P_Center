// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 封装unordered_set实现支持交集、并集的set
#ifndef P_CENTER_SET_H
#define P_CENTER_SET_H

#include <unordered_set>
#include <vector>
#include <iostream>

namespace edward {

class Set {
    std::unordered_set<int> set_;
public:
    Set() = default;
    ~Set() = default;
    explicit Set(const std::vector<int> &arr):set_(arr.begin(), arr.end()) {}
    void insert(int x) {
        set_.insert(x);
    }
    void erase(int x) {
        set_.erase(x);
    }
    int size() const {
        return set_.size(); //size_t -> int
    }
    bool empty() const {
        return set_.empty();
    }
    bool exist(int x) const {
        return set_.count(x) > 0;
    }
    const std::unordered_set<int>& getSet() const {
        return set_;
    }
    int getRandom() const;
    const Set& operator&= (const Set& rhs);
    const Set& operator|= (const Set& rhs);
    bool operator<= (const Set& rhs) const;   //check if it's a subset of the right-hand side.
    friend Set operator& (const Set& lhs, const Set& rhs);
    friend Set operator| (const Set& lhs, const Set& rhs);
    friend std::ostream& operator<< (std::ostream &os, const Set& rhs);
};

Set operator& (const Set& lhs, const Set& rhs);
Set operator| (const Set& lhs, const Set& rhs);
std::ostream& operator<< (std::ostream &os, const Set& rhs);

}


#endif //P_CENTER_SET_H
