// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description: Instance
#ifndef P_CENTER_INSTANCE_H
#define P_CENTER_INSTANCE_H

#include "Center.h"
#include "Element.h"
#include "PCenter.h"
#include "RandomSet.h"
#include "TabuList.h"
#include "RandomMap.h"

#include <vector>
#include <functional>
#include <unordered_map>

namespace edward {

class Instance {
    using Iter = std::vector<int>::iterator;
    int n_, k_;
    std::unordered_map<int, Center> centers_;
    std::unordered_map<int, Element> elements_;
    RandomMap<Center> qCenters_;
    RandomMap<Element> qElements_;
    szx::Centers &output_;  //reference
    //const std::function<bool()> &isTimeout_;

    RandomSet X_;
    std::vector<RandomSet> G_;    //G0 G1 G2
    int U_, U_star_;                 //|G0|
    int target_, target_star_;            //\forall e\in G0, \sum W_e
    std::pair<int, int> move_;
    TabuList tabuList_;


    bool reduceRD();
    bool reduceCD();
    bool reduceUC();
    bool isComplete() const;

    void removeRef(int idx, const Element& element);
    void removeRef(int idx, const Center& center);
    int getPDelta(int p);
    int getQDelta(int q);
    int insert(int p);
    void insert();
    int remove(int q);
    void remove();
    bool inTabuList(int x) const {
        return tabuList_.exist(x);
    }
    void removeTabu(std::vector<int>& arr);
    bool breakTabu1(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd);
    bool breakTabu2(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd);
    Iter partitionTabu(std::vector<int> &arr);          //divide arr elements into two parts based on whether belong to tabuList or not

    //return delta
    int search1(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd);    //search N3
    int search2(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd);    //search X

public:
    explicit Instance(const szx::PCenter& pCenter, szx::Centers& output);
    friend std::ostream& operator<< (std::ostream& os, const Instance& instance);
    void reduce();
    void getInit(); //generate initial solution
    bool isSolved() const {
        return U_ == 0;
    }
    bool findMove();
    void makeMove();
};

std::ostream& operator<< (std::ostream& os, const Instance& instance);

}


#endif //P_CENTER_INSTANCE_H
