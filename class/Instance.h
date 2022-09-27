// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description: Instance
#ifndef P_CENTER_INSTANCE_H
#define P_CENTER_INSTANCE_H

#include "RefMap.h"
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
    const int n_, k_;                                       //不变
    szx::Centers &output_;  //reference

    std::vector<Center> metaCenters_;       //中心元数据         //复用
    std::vector<Element> metaElements_;     //元素元数据         //复用
    RefMap<Center> centers_;                //中心集合          //复用
    RefMap<Element> elements_;              //元素集合          //复用

    /*
     * discarded
    std::unordered_map<int, Center> centers_;   //中心
    std::unordered_map<int, Element> elements_; //元素
    RandomMap<Center> qCenters_;
    RandomMap<Element> qElements_;
     */


    std::vector<std::pair<double, int>> alpha_;             //init时初始化
    RandomSet X_;                                           //需要重置
    std::vector<RandomSet> G_;    //G0 G1 G2                //需要重置
    int U_, U_star_;                 //|G0|                 //init时初始化
    int target_, target_star_; //\forall e\in G0, \sum W_e  //init时初始化
    std::pair<int, int> move_;                              //findMove初始化
    TabuList tabuList_;                                     //需要重置


    /*
    bool reduceRD();
    bool reduceCD();
    bool reduceUC();
    bool isComplete() const;

    void removeRef(int idx, const Element& element);
    void removeRef(int idx, const Center& center);
     */
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
    void reset();
    void reduceRadius(int centerIdx, int elementIdx);
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
