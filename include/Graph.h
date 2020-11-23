#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

enum state {
    Healthy,
    Contaminated,
    Infected
};

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    bool allInfected();

    void disconnectNode(int chosenNode);

    const std::vector<std::vector<int>> &getEdges() const;

    const std::vector<state> &getInfected() const;

private:
    std::vector<std::vector<int>> edges;
    std::vector<state> infected;
};

#endif