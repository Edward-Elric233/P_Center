// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/27
// Description: 
#include "Set.h"
#include "utils.h"

namespace edward {

const Set& Set::operator&=(const Set &rhs) {
    for (auto iter = set_.begin(); iter != set_.end(); ) {
        if (rhs.set_.count(*iter) == 0) {
            set_.erase(iter++);
        } else {
            ++iter;
        }
    }
    return *this;
}

const Set& Set::operator|=(const Set &rhs) {
    for (auto x : rhs.set_) {
        insert(x);
    }
    return *this;
}

bool Set::operator<=(const Set &rhs) const {
    //check if it's a subset of the right-hand side.
    for (auto x : set_) {
        if (!rhs.exist(x)) return false;
    }
    return true;
}

Set operator& (const Set& lhs, const Set& rhs) {
    if (lhs.size() > rhs.size()) {
        return operator&(rhs, lhs);
    } else {
        //lhs.size() <= rhs.size()
        Set ans;
        for (auto x : lhs.set_) {
            if (rhs.set_.count(x) > 0) {
                ans.insert(x);
            }
        }
        return ans;
    }
}
Set operator| (const Set& lhs, const Set& rhs) {
    //按秩合并
    if (lhs.size() > rhs.size()) {
        return operator|(rhs, lhs);
    } else {
        //lhs.size() <= rhs.size()
        Set ans = rhs;
        return ans |= lhs;
    }
}

std::ostream& operator<< (std::ostream &os, const Set& rhs) {
    for (auto x : rhs.set_) {
        os << x << " ";
    }
    return os;
}

int Set::getRandom() const {
    int idx = Random::rand(size());
    auto iter = set_.begin();
    while (idx--) ++iter;
    return *iter;
}

}

