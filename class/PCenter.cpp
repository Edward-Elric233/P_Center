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

            coverAllNodesUnderFixedRadius(output, input, isTimeout, seed);
            int iter = 0;
            edward::Timer timer;
            for (auto r = input.nodesWithDrops.begin(); !isTimeout() && (r != input.nodesWithDrops.end()); ++r) {
                timer.reset();
                reduceRadius(input, *r);
                coverAllNodesUnderFixedRadius(output, input, isTimeout, seed);
                //TODO
                edward::print("radius iter:", iter++);
                timer("radius time:");
            }
        }

        void coverAllNodesUnderFixedRadius(Centers& output, PCenter& input, std::function<bool()> isTimeout, int seed) {
            edward::Instance instance(input, output);
            //edward::print("test instance:", instance);
            edward::Timer timer;
            instance.reduce();
            timer("reduce time:");
//            edward::print("test instance after reduce:", instance);

            timer.reset();
            instance.getInit();
            timer("init time:");
            int iter = 0;
            while (!isTimeout() && !instance.isSolved()) {
                bool flag;
                timer.reset();
                while (!isTimeout() &&
                        !(flag = instance.findMove()));   //until find a legal move
                if (flag) instance.makeMove();
                //TODO:debug
                edward::print("[test] iterate count:", ++iter);
                timer("move time:");
            }
        }

        void reduceRadius(PCenter& input, Nodes nodesWithDrop) {
            for (auto n = nodesWithDrop.begin(); n != nodesWithDrop.end(); ++n) {
                input.coverages[*n].pop_back();
            }
        }
    };

// solver.
    void solvePCenter(Centers& output, PCenter& input, std::function<bool()> isTimeout, int seed) {
        Solver().solve(output, input, isTimeout, seed);
    }

}
