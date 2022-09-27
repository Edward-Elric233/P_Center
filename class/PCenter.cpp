// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/25
// Description: 
#include "PCenter.h"
#include "Instance.h"
#include "utils.h"

#include <random>
#include <iostream>


using namespace std;


namespace szx {

    class Solver {

    public:
        void solve(Centers& output, PCenter& input, std::function<bool()> isTimeout, int seed) {
            edward::Random::initRand(seed);
            edward::param::n = input.nodeNum;
            edward::Instance instance(input, output);

            coverAllNodesUnderFixedRadius(instance, output, input, isTimeout, seed);
            int iter = 0;
//            edward::Timer timer;
            for (auto r = input.nodesWithDrops.begin(); !isTimeout() && (r != input.nodesWithDrops.end()); ++r) {
//                timer.reset();
                reduceRadius(instance, input, *r);
                instance.reset();
                coverAllNodesUnderFixedRadius(instance, output, input, isTimeout, seed);
                //TODO:debug
//                edward::print("radius iter:", iter++);
//                timer("radius time:");
            }
        }

        void coverAllNodesUnderFixedRadius(edward::Instance &instance, Centers& output, PCenter& input, std::function<bool()> isTimeout, int seed) {
            //edward::print("test instance:", instance);
//            edward::Timer timer;
//            instance.reduce();
//            timer("reduce time:");
//            edward::print("test instance after reduce:", instance);

//            timer.reset();
            instance.getInit();
//            timer("init time:");
            int iter = 0;
            while (!isTimeout() && !instance.isSolved()) {
                bool flag;
//                timer.reset();
                while (!isTimeout() &&
                        !(flag = instance.findMove()));   //until find a legal move
                if (flag) instance.makeMove();
                //TODO:debug
//                edward::print("[test] iterate count:", ++iter);
//                timer("move time:");
            }
        }

        void reduceRadius(edward::Instance &instance, PCenter& input, Nodes &nodesWithDrop) {
            int centerIdx, elementIdx;
            for (auto n = nodesWithDrop.begin(); n != nodesWithDrop.end(); ++n) {
                auto &coverage = input.coverages[*n];
                centerIdx = *n;
                elementIdx = coverage.back();
                coverage.pop_back();
                instance.reduceRadius(centerIdx, elementIdx);
            }
        }
    };

// solver.
    void solvePCenter(Centers& output, PCenter& input, std::function<bool()> isTimeout, int seed) {
        Solver().solve(output, input, isTimeout, seed);
    }

}
