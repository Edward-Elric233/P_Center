//
// Created by Administrator on 2022/7/12.
//

#ifndef P_CENTER_QUICKMAP_H
#define P_CENTER_QUICKMAP_H

#include "utils.h"
#include "Vector.h"

namespace edward {

    template<typename T>    //int -> T
    class QuickMap {
        using Pair = std::pair<int const, T>;
        using Arr = Vector<T>;
        Arr arr_;
    public:
        QuickMap()
        : arr_(param::n) {
        }

        void insert(int idx, T&& item) {
            //TODO: important!!!, avoid memory leak
            arr_[idx] = std::move(item);
        }
        int size() const {
            return arr_.size();
        }
        T& operator[] (int x) {
            //if (!exist(x)) return T{};
            return arr_[x];
        }
    };
}


#endif //P_CENTER_QUICKMAP_H
