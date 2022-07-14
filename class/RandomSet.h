// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/7/4
// Description: 
#ifndef P_CENTER_RANDOMSET_H
#define P_CENTER_RANDOMSET_H

#include "utils.h"
#include "Vector.h"

namespace edward {

class RandomSet {
    using Vector = Vector<int>;
    Vector pos_, nums_;
public:
    explicit RandomSet(int n)
    : pos_(n, -1)
    , nums_(n) {
    }
    RandomSet()
    : pos_(param::n, -1)
    , nums_(param::n) {
    }
    RandomSet(RandomSet&& randomSet) noexcept
    : pos_(std::move(randomSet.pos_))
    , nums_(std::move(randomSet.nums_)) {

    }


    void insert(int x) {
        if (exist(x)) return;
        pos_[x] = nums_.size();
        nums_.push_back(x);
    }
    void erase(int x) {
        if (!exist(x)) return;
        int t = nums_.back();
        nums_[pos_[x]] = t;
        pos_[t] = pos_[x];
        pos_[x] = -1;
        nums_.pop_back();
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
    const Vector& getSet() const {
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
