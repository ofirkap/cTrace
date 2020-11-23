#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    Session(const std::string &path);

    Session(const Session &other);

    Session(Session &&other);

    Session &operator=(const Session &other);

    Session &operator=(Session &&other);

    virtual ~Session();

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    void enqueueInfected(int);

    int dequeueInfected();

    TreeType getTreeType() const;

    Graph getG() const;

    Graph& changeG();

    int gSize() const;

    const queue<int> &getInfected() const;

    int getCurrCycle() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    std::queue<int> infected;
    int currCycle;
};

#endif