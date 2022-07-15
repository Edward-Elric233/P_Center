//
// Created by Administrator on 2022/7/12.
//

#ifndef P_CENTER_RANDOMMAP_H
#define P_CENTER_RANDOMMAP_H

#include "utils.h"
#include "Vector.h"
#include <vector>
#include <unordered_map>

namespace edward {

    template<typename T>    //int -> T
    class RandomMap {
        using Pair = std::pair<int, T>;   //must be std::pair<const key_value, mapped_value>
        using Arr = std::vector<Pair>;
        Arr arr_;
        Vector<int> pos_;
    public:
        RandomMap()
        : pos_(param::n, -1)
        , arr_(param::n) {
            print("RandomMap ctor", param::n);
        }
        explicit RandomMap(int n)
        : pos_(n, -1)
        , arr_(n) {
            print("RandomMap ctor with arg", n);
        }
        bool empty() const {
            return arr_.empty();
        }
        Arr& getSet() {
            return arr_;
        }
        const Arr& getSet() const {
            return arr_;
        }
        bool exist(int x) const {
            return pos_[x] != -1;
        }
//        void insert(const Pair& pr) {
//            pos_[pr.first] = arr_.size();
//            arr_.push_back(std::move(pr));
//        }
        void emplace(int idx, const std::vector<int>& item) {
//            insert(Pair{idx, item});
            pos_[idx] = arr_.size();
            arr_.emplace_back(idx, item);
        }
        void erase(int x) {
            //if (!exist(x)) return;
            auto &last = arr_.back();
            arr_[pos_[x]] = std::move(last);
            pos_[last.first] = pos_[x];
            pos_[x] = -1;
            arr_.pop_back();
        }
        int size() const {
            return arr_.size();
        }
        T& operator[] (int x) {
            //if (!exist(x)) return T{};
            return arr_[pos_[x]].second;
        }
    };
}


#endif //P_CENTER_RANDOMMAP_H