//
// Created by Administrator on 2022/7/12.
//

#ifndef P_CENTER_RANDOMMAP_H
#define P_CENTER_RANDOMMAP_H

#include "utils.h"
#include <vector>

namespace edward {

    template<typename T>    //int -> T
    class RandomMap {
        using Pair = std::pair<int const, T>;   //important, avoid copy of insert's arguments
        using Arr = std::vector<T>;
        Arr arr_;
        std::vector<int> pos_;
    public:
        RandomMap(): pos_(param::n, -1) {
            arr_.reserve(param::n);
        }
        explicit RandomMap(int n): pos_(n, -1) {
            arr_.reserve(n);
        }
        bool empty() const {
            return arr_.empty();
        }
        Arr& getSet() {
            return arr_;
        }
        bool exist(int x) const {
            return pos_[x] != -1;
        }
        void insert(const Pair& pr) {
            //if (exist(x)) return;
            pos_[pr.first] = arr_.size();
            arr_.push_back(pr.second);
        }
        /*
        void erase(int x) {
            //if (!exist(x)) return;
            auto &last = arr_.back();
            arr_[pos_[x]] = last;
            pos_[last.first] = pos_[x];
            pos_[x] = -1;
            arr_.pop_back();
        }
        */
        int size() const {
            return arr_.size();
        }
        T& operator[] (int x) {
            //if (!exist(x)) return T{};
            return arr_[pos_[x]];
        }
    };
}


#endif //P_CENTER_RANDOMMAP_H
