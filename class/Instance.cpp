// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/28
// Description:
#include <climits>
#include "Instance.h"
#include "utils.h"

namespace edward {

Instance::Instance(const szx::PCenter &pCenter, szx::Centers &output)
    : output_(output)
    , n_(pCenter.nodeNum)
    , X_(n_)
    , tabuList_(n_)
    , alpha_(n_)
    , metaCenters_(n_)
    , metaElements_(n_)
    , centers_(metaCenters_)
    , elements_(metaElements_)
    , k_(pCenter.centerNum) {
    G_.resize(3);
    for (int i = 0; i < pCenter.nodeNum; ++i) {
        auto &coverages = pCenter.coverages[i];
        metaCenters_[i].init(coverages);
        metaCenters_[i].setIdx(i);
        metaElements_[i].setIdx(i);
        for (auto j : coverages) {
            //i cover j
            metaElements_[j].covered(i);
        }
    }
}

void Instance::reset() {
    X_.reset();
    for (auto &Gi_ : G_) Gi_.reset();
    tabuList_.reset();
    centers_.reset();
    elements_.reset();
    for (auto &element : metaElements_) {
        element.reset();
    }
    //metaCenters 不需要reset，没有什么操作
}

void Instance::reduceRadius(int centerIdx, int elementIdx) {
    //change meta data
    metaCenters_[centerIdx].removeCover(elementIdx);
    metaElements_[elementIdx].removeCovered(centerIdx);
}

std::ostream& operator<< (std::ostream& os, const Instance& instance) {
    std::cerr << "this function had been discarded!!!" << std::endl;
    return os;
}

/*
void Instance::removeRef(int idx, const Element &element) {
    for (auto x : element.getB().getSet()) {
        centers_[x].removeCover(idx);
    }
}

void Instance::removeRef(int idx, const Center &center) {
    for (auto x : center.getC().getSet()) {
        elements_[x].removeCovered(idx);
    }
}

bool Instance::reduceRD() {
    bool flag = false;
    for (auto iter1 = elements_.begin(); iter1 != elements_.end(); ++iter1) {
        for (auto iter2 = elements_.begin(); iter2 != elements_.end(); ) {
            if (iter1 == iter2) {
                ++iter2;
                continue;
            }
            if (iter1->second.isDominate(iter2->second)) {
                //eliminate iter2->second
                removeRef(iter2->first, iter2->second);
                elements_.erase(iter2++);
                flag = true;
            } else {
                ++iter2;
            }
        }
    }
    //print("test reduceRD:", *this);
    return flag;
}

bool Instance::reduceCD() {
    bool flag = false;
    for (auto iter1 = centers_.begin(); iter1 != centers_.end(); ++iter1) {
        for (auto iter2 = centers_.begin(); iter2 != centers_.end(); ) {
            if (iter1 == iter2) {
                ++iter2;
                continue;
            }
            if (iter1->second.isDominate(iter2->second)) {
                //eliminate iter2->second
                removeRef(iter2->first, iter2->second);
                centers_.erase(iter2++);
                flag = true;
            } else {
                ++iter2;
            }
        }
    }
    //print("test reduceCD:", *this);
    return flag;
}

bool Instance::reduceUC() {
    bool flag = false;
    for (auto iter = elements_.begin(); iter != elements_.end(); ) {
        if (iter->second.isSingleCovered()) {
            //we must pick set s in order to cover e
            int idx = output_[--k_] = *(iter->second.getB().getSet().begin());

            auto center_iter = centers_.find(idx);

            //eliminate set s and all elements covered by set s

            std::vector<int> elems;
            for (auto x : center_iter->second.getC().getSet()) {
                elems.push_back(x);
                //CANNOT delet elements while traversing it, we use a auxiliary array 'elemts' to store elements idx.
            }
            for (auto x : elems) {
                //eliminate all elements covered by set s
                auto elem_iter = elements_.find(x);
                removeRef(elem_iter->first, elem_iter->second);

                if (iter == elem_iter) ++iter; //increase iter, otherwise it will be eliminated later.

                elements_.erase(elem_iter);
            }
            removeRef(center_iter->first, center_iter->second); //unnecessary
            centers_.erase(center_iter);
            //print("test reduceUC:", *this);
            flag = true;
        } else {
            ++iter;
        }
    }
    //print("test reduceUC:", *this);
    return flag;
}

bool Instance::isComplete() const {
    //检查每个元素都有被覆盖
    for (auto &&[idx, element] : elements_) {
        if (!element.isCovered()) return false;
    }
    return true;
}

void Instance::reduce() {
    bool flag;
    do {
        flag = false;
        flag |= reduceRD();
        flag |= reduceCD();
        flag |= reduceUC();
    } while (flag);
    if (centers_.size() < k_) {
        RandomSet T;
        for (int i = 0; i < n_; ++i) T.insert(i);
        int t = 0;
        for (auto &&[idx, center] : centers_) {
            T.erase(idx); //remove the rest of centers
            output_[t++] = idx;
        }
        //t = centers.size()

        for (auto iter = output_.begin() + k_; iter != output_.end(); ++iter) {
            T.erase(*iter); //remove confirmed centers
        }
        for (int i = centers_.size(); i < k_; ++i) {
            //random select center
            output_[i] = *T.getSet().begin();
            T.erase(output_[i]);
        }
        k_ = 0;
    }

}
 */

void Instance::getInit() {
    //calculate alpha for every set
    constexpr double ALPHA = 100.0;
    for (auto &&center : centers_) {
        int idx = center.getIdx();
        double sum = 0;
        for (auto e : center.getC().getSet()) {
            sum += ALPHA / elements_[e].getB().size();
        }
        //getInit is called after reset, so idx is increasement
        alpha_[idx] = {sum, idx};
    }
    std::sort(alpha_.begin(), alpha_.end(), std::greater<std::pair<double,int>>());

    int t;
    for (int i = 0; i < k_; ++i) {
        t = alpha_[i].second;
        X_.insert(t);
        //X_star <- X
        output_[i] = t;
    }

    std::unordered_map<int, int> cnt;   //record solution X cover elements's times
    for (auto s : X_.getSet()) {
        for (auto e : centers_[s].getC().getSet()) {
            ++cnt[e];
        }
    }

    for (auto &&element : elements_) {
        int idx = element.getIdx();
        int t = cnt[idx];
        element.setG(t);
        G_[t > 1 ? 2 : t].insert(idx);
    }

    U_ = G_[0].size();
    U_star_ = U_;   //X_star
    target_ = 0;
    for (auto e : G_[0].getSet()) {
        target_ += elements_[e].getW();
    }
    target_star_ = target_;

    /*
    //get N^3
    for (auto &&element : elements_) {
        int idx = element.getIdx();
        Set E;  //N^2
        for(auto s : element.getB().getSet()) { //N^1
            for (auto e : centers_[s].getC().getSet()) {
                if (e != idx) E.insert(e);
            }
        }
        for (auto e : E.getSet()) {
            for (auto s : elements_[e].getB().getSet()) {
                if (!element.getB().exist(s)) { //s not in N^1
                    element.insertN3(s);
                }
            }
        }
    }
     */

}

/*!
 * calc delta after add p in X
 * @param p
 * @return
 */
int Instance::getPDelta(int p) {
    int delta = 0;
    auto &G0 = G_[0];
    for (auto e : centers_[p].getC().getSet()) {
        if (G0.exist(e)) {
            delta -=  elements_[e].getW();
        }
    }
    return delta;
}

int Instance::getQDelta(int q) {
    int delta = 0;
    auto G1 = G_[1];
    for (auto e : centers_[q].getC().getSet()) {
        if (G1.exist(e)) {
            delta += elements_[e].getW();
        }
    }
    return delta;
}

void Instance::insert() {
    int p = move_.first;
    X_.insert(p);
    for (auto e : centers_[p].getC().getSet()) {
        auto &element = elements_[e];
        if (element.getG() == 0) {
            G_[0].erase(e);
            G_[1].insert(e);
        } else if (element.getG() == 1) {
            G_[1].erase(e);
            G_[2].insert(e);
        }
        element.incG();
    }
}

int Instance::insert(int p) {
    //X | {p}
    X_.insert(p);
    int delta = 0;
    for (auto e : centers_[p].getC().getSet()) {
        auto &element = elements_[e];
        if (element.getG() == 0) {
            delta -= element.getW();
            G_[0].erase(e);
            G_[1].insert(e);
        } else if (element.getG() == 1) {
            G_[1].erase(e);
            G_[2].insert(e);
        }
        element.incG();
    }
    return delta;
}

void Instance::remove() {
    int q = move_.second;
    X_.erase(q);
    for (auto e : centers_[q].getC().getSet()) {
        auto &element = elements_[e];
        if (element.getG() == 1) {
            G_[1].erase(e);
            G_[0].insert(e);
        } else if (element.getG() == 2) {
            G_[2].erase(e);
            G_[1].insert(e);
        }
        element.decG();
    }
}

int Instance::remove(int q) {
    //X \ {q}
    X_.erase(q);
    int delta = 0;
    for (auto e : centers_[q].getC().getSet()) {
        auto &element = elements_[e];
        if (element.getG() == 1) {
            delta += element.getW();
            G_[1].erase(e);
            G_[0].insert(e);
        } else if (element.getG() == 2) {
            G_[2].erase(e);
            G_[1].insert(e);
        }
        element.decG();
    }
    return delta;
}

void Instance::removeTabu(std::vector<int> &arr) {
    std::vector<int> tmp;
    for (auto x : arr) {
        if (!inTabuList(x)) tmp.push_back(x);
    }
    if (tmp.empty() && G_[0].size() == 1) {
        //hit a dead end

    } else {
        arr = std::move(tmp);
    }
}

/*!
 * 将arr原地划分为两部分：不在禁忌表和在禁忌表，复杂度为O(n)
 * @param arr
 * @return 分界点
 */
Instance::Iter Instance::partitionTabu(std::vector<int> &arr) {
    auto head = arr.begin(), tail = arr.end();
    while (head != tail) {
        if (!inTabuList(*head)) ++head;
        else {
            //inTabuList
            --tail;
            std::swap(*head, *tail);
        }
    }
    /*
    if (head == arr.begin() && G_[0].size() == 1) {
        //如果整个数组都在禁忌表中(覆盖某个元素的中心只有一个，刚刚被移出解，导致这个元素无法被覆盖)，而且只有一个未覆盖元素(随机无法跳出停滞)
        //有了破禁规则，不需要
        head = arr.end();
    }
     */
    return head;    //head == tail
}

bool Instance::breakTabu1(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd) {
    int delta = search1(pBegin, pEnd, qBegin, qEnd);
    if (delta < INF && target_ + delta < target_star_) {
        target_star_ = target_ + delta;
        return true;
    } else {
        return false;
    }
}

bool Instance::breakTabu2(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd) {
    int delta = search2(pBegin, pEnd, qBegin, qEnd);
    if (delta < INF && target_ + delta < target_star_) {
        target_star_ = target_ + delta;
        return true;
    } else {
        return false;
    }
}

/*!
 * search P * Q
 * @param pBegin
 * @param pEnd
 * @param qBegin
 * @param qEnd
 * @return delta
 */
int Instance::search1(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd) {
    int minDelta = INF, delta, pDelta, qDelta, minQDelta, minQ;
    int p, q;
    for (auto pIter = pBegin; pIter != pEnd; ++pIter) {
        p = *pIter;
//            if (inTabuList(p)) continue;
        //X | {p}
        pDelta = insert(p);

        minQDelta = INF;
        minQ = -1;
        for (auto qIter = qBegin; qIter != qEnd; ++qIter) {
            q = *qIter;
//                if (inTabuList(q)) continue;
            qDelta = getQDelta(q);
            if (qDelta < minQDelta) {
                minQDelta = qDelta;
                minQ = q;
            }
        }
        if (minQDelta < INF) {
            delta = pDelta + minQDelta;
            if (delta < minDelta) {
                minDelta = delta;
                move_ = {p, minQ};
            }
        }

        remove(p);

    }
    return minDelta;
}

/*!
 * search P + Q
 * @param pBegin
 * @param pEnd
 * @param qBegin
 * @param qEnd
 * @return delta
 */
int Instance::search2(Iter pBegin, Iter pEnd, Iter qBegin, Iter qEnd) {
    int minPDelta = INF, minQDelta = INF, pDelta, qDelta, p, q;
    for (auto pIter = pBegin; pIter != pEnd; ++pIter) {
        p = *pIter;
//            if (inTabuList(p)) continue;
        pDelta = getPDelta(p);
        if (pDelta < minPDelta) {
            minPDelta = pDelta;
            move_.first = p;
        }
    }
    for (auto qIter = qBegin; qIter != qEnd; ++qIter) {
        q = *qIter;
//            if (inTabuList(q)) continue;
        qDelta = getQDelta(q);
        if (qDelta < minQDelta) {
            minQDelta = qDelta;
            move_.second = q;
        }
    }
    if (minPDelta < INF && minQDelta < INF) return minPDelta + minQDelta;
    else return INF;
}

bool Instance::findMove() {
    int t = G_[0].getRandom();
    auto &elem_star = elements_[t];
    auto P = elem_star.getB().getSet();
    auto Q = X_.getSet();
    auto PTabu = partitionTabu(P);
    auto QTabu = partitionTabu(Q);

    if (breakTabu1(PTabu, P.end(), QTabu, Q.end())) return true;
    int delta = search1(P.begin(), PTabu, Q.begin(), QTabu);
    if (delta < INF) {
        target_ += delta;
        if (target_ < target_star_) {
            target_star_ = target_;
        }
        return true;
    } else {
        return false;
    }

}

void Instance::makeMove() {
    static int moveIter = 0;
    static int LIMIT = 1e4;
    /*
     * 1e4: 2.4s
     */
    int oldU = U_;
//    target_ += insert(move_.first) + remove(move_.second);
    insert();
    remove();
    U_ = G_[0].size();
    ++moveIter;
    //TODO:debug
//    print("[test] {", U_, "} move: [", move_.first, move_.second, "]", "moveIter = ", moveIter, "tabuList size:", tabuList_.size());

    if (U_ < U_star_) {
        //X_star <- X
        int idx = 0;
        for (auto s : X_.getSet()) {
            output_[idx++] = s;
        }
        U_star_ = U_;
        moveIter = 0;
    }
    if (U_ >= oldU){
        for (auto e : G_[0].getSet()) {
            elements_[e].incW();
        }
    }
    if (moveIter > LIMIT) {
        tabuList_.expand();
        moveIter = 0;
        LIMIT = INF;
    }
    tabuList_.add(move_);
}

}