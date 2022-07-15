//
// Created by Administrator on 2022/7/6.
//

#ifndef P_CENTER_TABULIST_H
#define P_CENTER_TABULIST_H

#include <vector>
#include "utils.h"

namespace edward {

/*
 * O(1) query insert
 * initialize after instance: must use param::n
 */
class TabuList {
    int capacity_;  //default = 2
    int idx_;
    //TODO: use Vector
    std::vector<int> vis_, nums_;

    void insert(int x) {
        vis_[x] = 1;
        if (nums_.size() < capacity_) {
            nums_.push_back(x);
        } else {
            //delete nums[idx]
            vis_[nums_[idx_]] = 0;
            nums_[idx_++] = x;
            if (idx_ >= capacity_) idx_ = 0;
        }
    }
public:
    TabuList()
    : vis_(param::n, 0)
    , idx_(0)
    , capacity_(2) {

    }
    void add(const std::pair<int, int> &pr) {
        insert(pr.first);
        insert(pr.second);
    }
    bool exist(int x) const {
        return vis_[x];
    }
    void expand() {
        capacity_ = capacity_ << 1;
    }
    int size() const {
        return nums_.size();
    }

    friend std::ostream& operator<< (std::ostream&os, const TabuList& tabuList);
};

std::ostream& operator<< (std::ostream&os, const TabuList& tabuList);

}



#endif //P_CENTER_TABULIST_H
