// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/6/25
// Description: 
#ifndef P_CENTER_PCENTER_H
#define P_CENTER_PCENTER_H




#include <vector>
#include <functional>


namespace szx {

    using NodeId = int;
    using EdgeId = NodeId;
    using Nodes = std::vector<NodeId>;

    struct PCenter {
        NodeId nodeNum;
        NodeId centerNum;
        std::vector<Nodes> coverages; // `coverages[n]` are the nodes covered by node `n` if node `n` is a center.
        std::vector<Nodes> nodesWithDrops; // `nodesWithDrops[r]` are the nodes which will drop its farthest covering node in the `r`th radius reduction.
    };

    using Centers = Nodes; // `Centers[k]` is the `k`th picked center.


    void solvePCenter(Centers& output, PCenter& input, std::function<bool()> isTimeout, int seed);

}




#endif //P_CENTER_PCENTER_H
