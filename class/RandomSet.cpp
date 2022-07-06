// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/7/4
// Description: 
#include "RandomSet.h"

namespace edward {

std::ostream& operator<< (std::ostream& os, const RandomSet& randomSet) {
    for (auto x : randomSet.nums_) {
        os << x << " ";
    }
    return os;
}

bool RandomSet::operator<=(const RandomSet &randomSet) const {
    for (auto x : nums_) {
        if (!randomSet.exist(x)) return false;
    }
    return true;
}

std::vector<int> operator &(const RandomSet& lhs, const RandomSet &rhs) {
    if (lhs.size() > rhs.size()) {
        return operator&(rhs, lhs);
    } else {
        //lhs.size() <= rhs.size()
        std::vector<int> ans;
        for (auto x : lhs.getSet()) {
            if (rhs.exist(x)) {
                ans.push_back(x);
            }
        }
        return ans;
    }
}

}