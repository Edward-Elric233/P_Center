// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/7/4
// Description: 
#include "RandomSet.h"

namespace edward {

std::ostream& operator<< (std::ostream& os, const RandomSet& randomSet) {
    auto &vec = randomSet.nums_;
    auto p = vec.p_;
    int len = vec.idx_;
    for (int i = 0; i < len; ++i) {
        os << p[i] << " ";
    }
    /*
    for (auto x : randomSet.nums_) {
        os << x << " ";
    }
     */
    return os;
}

bool RandomSet::operator<=(const RandomSet &randomSet) const {
    auto &vec = nums_;
    auto p = vec.p_;
    int len = vec.idx_;
    for (int i = 0; i < len; ++i) {
        if (!randomSet.exist(p[i])) return false;
    }
    /*
    for (auto x : nums_) {
        if (!randomSet.exist(x)) return false;
    }
     */
    return true;
}

std::vector<int> operator &(const RandomSet& lhs, const RandomSet &rhs) {
    if (lhs.size() > rhs.size()) {
        return operator&(rhs, lhs);
    } else {
        //lhs.size() <= rhs.size()
        std::vector<int> ans;

        auto &vec = lhs.getSet();
        auto p = vec.p_;
        int len = vec.idx_;
        for (int i = 0; i < len; ++i) {
            if (rhs.exist(p[i])) {
                ans.push_back(p[i]);
            }
        }

        /*
        for (auto x : lhs.getSet()) {
            if (rhs.exist(x)) {
                ans.push_back(x);
            }
        }
         */
        return ans;
    }
}

}