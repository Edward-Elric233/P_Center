// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description: Center
#ifndef P_CENTER_CENTER_H
#define P_CENTER_CENTER_H

#include <vector>
#include "Set.h"
#include "RandomSet.h"

namespace edward {

class Center {
    RandomSet C_; // the set of elements covered by this center
public:
    Center() = default;
    ~Center() = default;

    void reset() {

    }

    void init(const std::vector<int>& arr) {
        for (auto x : arr) C_.insert(x);
    }

    void removeCover(int x) {
        //TODO: recalculate alpha
        C_.erase(x);
    }

    const RandomSet& getC() const {
        return C_;
    }

    bool isDominate(const Center& other) const {
        return other.C_ <= C_;
    }

    friend std::ostream& operator<< (std::ostream& os, const Center& center);
};

std::ostream& operator<< (std::ostream& os, const Center& center);

}

#endif //P_CENTER_CENTER_H
