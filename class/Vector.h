//
// Created by Administrator on 2022/7/13.
//

#ifndef P_CENTER_VECTOR_H
#define P_CENTER_VECTOR_H

#include <utility>

namespace edward {

    template<typename T>
    class Vector {
        T *p_;
        int idx = 0;
    public:
        explicit Vector(int n): p_(new T[n]) {

        }
        Vector(int n, T val): p_(new T[n]) {
            for (int i = 0; i < n; ++i) {
                p_[i] = val;
            }
        }
        T& operator[] (int n) {
            return p_[n];
        }
        void push_back(const T& val) {
            p_[idx++] = val;
        }
        void push_back(T&& val) {
            p_[idx++] = std::move(val);
        }
        void pop_back() {
            --idx;
        }
    };

}


#endif //P_CENTER_VECTOR_H
