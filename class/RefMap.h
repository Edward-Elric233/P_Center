//
// Created by edward on 22-9-19.
//

#ifndef P_CENTER_REFMAP_H
#define P_CENTER_REFMAP_H

#include "RandomSet.h"

/*
 * 通过封装一个RandomSet访问元数据，表现得像一个RandomMap
 */
template<typename T>
class RefMap {
    using MetaData = std::vector<T>;
    MetaData &metaDatas_;
    edward::RandomSet set_;
public:
    RefMap(MetaData &arr): metaDatas_(arr) {
        //初始化时所有元素都在集合中
        set_.fill();
    }
    bool empty() const {
        return set_.empty();
    }
    bool exist(int x) const {
        return set_.exist(x);
    }
    void insert(int x) {
        set_.insert(x);
    }
    void reset() {
        set_.fill();
    }
    void erase(int x) {
        set_.erase(x);
    }
    int size() const {
        return set_.size();
    }
    T& operator[](int x) {
        return metaDatas_[x];
    }
};


#endif //P_CENTER_REFMAP_H
