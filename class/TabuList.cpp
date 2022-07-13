//
// Created by Administrator on 2022/7/6.
//

#include "TabuList.h"

namespace edward {


std::ostream& operator<< (std::ostream&os, const TabuList& tabuList) {
    for (auto x : tabuList.nums_) os << x << " ";
    return os;
}


}