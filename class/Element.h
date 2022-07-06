// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description: Element
#ifndef P_CENTER_ELEMENT_H
#define P_CENTER_ELEMENT_H

#include "RandomSet.h"

namespace edward {

class Element {
    RandomSet B_; //the set of centers covering this element
    RandomSet N3_;//N^3
    int G_ = 0, W_ = 1;
public:
    Element() = default;
    ~Element() = default;

    int getG() const {
        return G_;
    }

    void setG(int g) {
        G_ = g;
    }

    void incG() {
        ++G_;
    }

    void decG() {
        --G_;
    }

    int getW() const {
        return W_;
    }

    void setW(int w) {
        W_ = w;
    }

    void incW() {
        static constexpr int MAXW = 1 << 16;
        if (++W_ > MAXW) {  //smooth inc
            W_ /= 2;
        }
    }

    void insertN3(int x) {
//        if (!N3_.exist(x))
            N3_.insert(x);
    }

    const RandomSet& getN3() const {
        return N3_;
    }

    void covered(int x) {
        B_.insert(x);
    }
    bool isCovered() const {
        return !B_.empty();
    }
    bool isDominate(const Element& other) const {
        return B_ <= other.B_;
    }
    const RandomSet& getB() const {
        return B_;
    }
    void removeCovered(int x) {
        B_.erase(x);
    }
    bool isSingleCovered() const {
        return B_.size() == 1;
    }

    friend std::ostream& operator<< (std::ostream& os, const Element& element);
};

std::ostream& operator<< (std::ostream& os, const Element& element);

}

#endif //P_CENTER_ELEMENT_H
