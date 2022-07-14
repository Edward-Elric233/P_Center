//
// Created by Administrator on 2022/7/13.
//

#ifndef P_CENTER_VECTOR_H
#define P_CENTER_VECTOR_H

#include "utils.h"
#include <utility>
#include <vector>

namespace edward {

    template<typename T>
    class Vector {
    public:
        T *p_;
        int idx_ = 0;
        explicit Vector(int n): p_(new T[n]) {

        }
        Vector(int n, T val): p_(new T[n]) {
            for (int i = 0; i < n; ++i) {
                p_[i] = val;
            }
        }
        Vector(const Vector& vector) {
//            print("copy ctor");
            p_ = vector.p_;
            idx_ = vector.idx_;
        }
        Vector(Vector&& vector) noexcept
        : p_ (vector.p_)
        , idx_(vector.idx_) {
//            print("move ctor");
            vector.p_ = nullptr;
        }
        void operator= (const Vector& vector) {
//            print("copy assignment");
            p_ = vector.p_;
            idx_ = vector.idx_;
        }
        ~Vector() {
//            print("Vector dtor");
//            delete[] p_;
        }
        T& operator[] (int n) {
            return p_[n];
        }
        const T& operator[] (int n) const {
            return p_[n];
        }
        void push_back(const T& val) {
            p_[idx_++] = val;
        }
        void push_back(T&& val) {
            p_[idx_++] = std::move(val);
        }
        void pop_back() {
            --idx_;
        }
        int size() const {
            return idx_;
        }
        const T& back() const {
            return p_[idx_ - 1];
        }
        bool empty() const {
            return idx_ == 0;
        }
        std::vector<int> getVec() const {
            std::vector<int> ret;
            for (int i = 0; i < idx_; ++i) ret.push_back(p_[i]);
            return ret;
        }
        const T& front() const {
            return p_[0];
        }
    };

}


#endif //P_CENTER_VECTOR_H
