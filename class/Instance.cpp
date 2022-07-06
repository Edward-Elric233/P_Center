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
    , X_(pCenter.nodeNum)
    , n_(pCenter.nodeNum)
    , tabuList_(pCenter.nodeNum)
    , k_(pCenter.centerNum) {
    param::n = pCenter.nodeNum;
    G_.resize(3);
    for (int i = 0; i < pCenter.nodeNum; ++i) {
        auto &coverages = pCenter.coverages[i];
        centers_.emplace(i, coverages);
        for (auto j : coverages) {
            //i cover j
            elements_[j].covered(i);
        }
    }
}

std::ostream& operator<< (std::ostream& os, const Instance& instance) {
    print("k = ", instance.k_);
    for (auto &&[idx, center] : instance.centers_) {
        print("center", idx, ":", center);
    }
    for (auto &&[idx, element] : instance.elements_) {
        print("element", idx, ":", element);
    }
    return os;
}

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

void Instance::getInit() {
    //calculate alpha for every set
    constexpr double ALPHAE = 100.0;
    std::vector<std::pair<double, int>> alpha;
    for (auto &&[idx, center] : centers_) {
        double sum = 0;
        for (auto e : center.getC().getSet()) {
            sum += ALPHAE / elements_[e].getB().size();
        }
        alpha.emplace_back(sum, idx);
    }
    std::sort(alpha.begin(), alpha.end(), std::greater<std::pair<double,int>>());

    int t;
    for (int i = 0; i < k_; ++i) {
        t = alpha[i].second;
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

    for (auto &&[idx, element] : elements_) {
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

    //get N^3
    for (auto &&[idx, element] : elements_) {
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
}

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

bool Instance::findMove() {
    int t = G_[0].getRandom();
    auto &elem_star = elements_[t];
    auto P = elem_star.getB().getSet();
    auto Q = X_ & elem_star.getN3();
    removeTabu(P);
    removeTabu(Q);
    if (Q.empty()) {
        auto Q_ = X_.getSet();
        removeTabu(Q_);
        int minPDelta = INF, minQDelta = INF, pDelta, qDelta;
        bool pFlag = false, qFlag = false;
        for (auto p : P) {
//            if (inTabuList(p)) continue;
            pDelta = getPDelta(p);
            if (pDelta < minPDelta) {
                minPDelta = pDelta;
                move_.first = p;
                pFlag = true;
            }
        }
        for (auto q : Q_) {
//            if (inTabuList(q)) continue;
            qDelta = getQDelta(q);
            if (qDelta < minQDelta) {
                minQDelta = qDelta;
                move_.second = q;
                qFlag = true;
            }
        }
        return pFlag && qFlag;
    } else {
        int minDelta = INF, delta, pDelta, qDelta, minQDelta, minQ;
        bool flag = false;
        for (auto p : P) {
//            if (inTabuList(p)) continue;
            //X | {p}
            pDelta = insert(p);

            minQDelta = INF;
            minQ = -1;
            for (auto q : Q) {
//                if (inTabuList(q)) continue;
                qDelta = getQDelta(q);
                if (qDelta < minQDelta) {
                    minQDelta = qDelta;
                    minQ = q;
                    flag = true;
                }
            }
            delta = pDelta + minQDelta;
            if (delta < minDelta) {
                minDelta = delta;
                move_ = {p, minQ};
            }

            remove(p);

        }
        return flag;
    }

}

void Instance::makeMove() {
    static int moveIter = 0;
    static constexpr int LIMIT = 5e3;
    /*
     * 1e4: 2.4s
     */
    int oldU = U_;
    target_ += insert(move_.first) + remove(move_.second);
    U_ = G_[0].size();
    ++moveIter;
    print("[test]", U_, "move: [", move_.first, move_.second, "]", "moveIter = ", moveIter, "tabuList size:", tabuList_.size());

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
    }
    tabuList_.add(move_);
}

}