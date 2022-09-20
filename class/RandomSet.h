// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/7/4
// Description: 
#ifndef P_CENTER_RANDOMSET_H
#define P_CENTER_RANDOMSET_H

#include <vector>
#include "utils.h"

namespace edward {

class RandomSet {
    std::vector<int> pos_, nums_;
public:
    explicit RandomSet(int n)
    : pos_(n, -1) {
        nums_.reserve(n);
    }
    RandomSet()
    : pos_(param::n, -1) {
        nums_.reserve(param::n);
    }

    void insert(int x) {
        if (exist(x)) return;
        pos_[x] = nums_.size();
        nums_.push_back(x);
    }
    void erase(int x) {
        if (!exist(x)) return;
        nums_[pos_[x]] = nums_.back();
        pos_[nums_.back()] = pos_[x];
        pos_[x] = -1;
        nums_.pop_back();
    }
    void fill() {
        //置位操作
        nums_.clear();
        for (int i = 0; i < pos_.size(); ++i) {
            insert(i);
        }
    }
    void reset() {
        //置0操作
        nums_.clear();
        for (int i = 0; i < pos_.size(); ++i) {
            pos_[i] = -1;
        }
    }
    int size() const {
        return nums_.size(); //size_t -> int
    }
    bool empty() const {
        return nums_.empty();
    }
    bool exist(int x) const {
        return pos_[x] != -1;
    }
    const std::vector<int>& getSet() const {
        return nums_;
    }
    int getRandom() const {
        return nums_[Random::rand(nums_.size())];
    }
    bool operator<= (const RandomSet& randomSet) const;
    friend std::vector<int> operator &(const RandomSet& lhs, const RandomSet &rhs);
    friend std::ostream& operator<< (std::ostream& os, const RandomSet& randomSet);
};

std::vector<int> operator &(const RandomSet& lhs, const RandomSet &rhs);
std::ostream& operator<< (std::ostream& os, const RandomSet& randomSet);

}


#endif //P_CENTER_RANDOMSET_H
