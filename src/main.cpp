#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include "PCenter.h"
#include "test.h"
#include "utils.h"


using namespace std;
using namespace szx;


void loadInput(istream& is, PCenter& pc) {
    is >> pc.nodeNum >> pc.centerNum;
    pc.coverages.resize(pc.nodeNum);
    for (auto coverage = pc.coverages.begin(); coverage != pc.coverages.end(); ++coverage) {
        NodeId coveredNodeNum;
        is >> coveredNodeNum;
        coverage->resize(coveredNodeNum);
        for (auto node = coverage->begin(); node != coverage->end(); ++node) { is >> *node; }
    }

    EdgeId minEdgeLenRank;
    EdgeId maxEdgeLenRank;
    is >> maxEdgeLenRank >> minEdgeLenRank;
    pc.nodesWithDrops.resize(maxEdgeLenRank - minEdgeLenRank);
    for (auto r = pc.nodesWithDrops.begin(); r != pc.nodesWithDrops.end(); ++r) {
        NodeId nodeNumToDrop;
        is >> nodeNumToDrop;
        r->resize(nodeNumToDrop);
        for (auto node = r->begin(); node != r->end(); ++node) { is >> *node; }
    }
}

void saveOutput(ostream& os, Centers& centers) {
    for (auto center = centers.begin(); center != centers.end(); ++center) { os << *center << endl; }
}

void test(istream& inputStream, ostream& outputStream, long long secTimeout, int randSeed) {
    cerr << "load input." << endl;
    PCenter pc;
    loadInput(inputStream, pc);

    cerr << "solve." << endl;
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now() + chrono::milliseconds(secTimeout * 1000 - 1);
    Centers centers(pc.centerNum);
    solvePCenter(centers, pc, [&]() -> bool { return endTime < chrono::steady_clock::now(); }, randSeed);

    cerr << "save output." << endl;
    saveOutput(outputStream, centers);
}
void test(istream& inputStream, ostream& outputStream, long long secTimeout) {
    return test(inputStream, outputStream, secTimeout, static_cast<int>(time(nullptr) + clock()));
}


int main(int argc, char* argv[]) {
    cerr << "load environment." << endl;
    if (argc != 3) {
        cerr << "you should run program with two arguments" << endl;
        return -1;
    }
    long long secTimeout = atoll(argv[1]);
//    int randSeed = atoi(argv[2]);
    int randSeed = 123456;

    //std::string fileName = "sample";
//    std::string fileName = "pmed19.n400p080";
//    std::string fileName = "rl1323p070";
//    std::string fileName = "rl1323p030";
//    std::string fileName = "u1817p020";
//    std::string fileName = "u1817p010";
    std::string fileName = "u1817p130";
//    std::string fileName = "pmed06.n200p005";
//    std::string fileName = "pcb3038p010r729";
#ifdef __WIN32__
    ifstream ifs("..\\data\\input\\" + fileName + ".txt");
    ofstream ofs("..\\data\\output\\" + fileName + ".txt");
    edward::print("Windwos");
#elif __linux__
    ifstream ifs("../data/input/" + fileName + ".txt");
    ofstream ofs("../data/output/" + fileName + ".txt");
//    edward::print("Linux");
#endif
    //test(ifs, ofs, secTimeout); // for self-test.
    edward::Timer timer;
    test(ifs, ofs, secTimeout, randSeed);
    timer("[test] run time:");

//    test(cin, cout, secTimeout, randSeed)
    return 0;
}
