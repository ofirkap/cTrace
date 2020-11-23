#include "../include/Graph.h"


Graph::Graph(std::vector<std::vector<int>> matrix) : edges(std::move(matrix)),
                                                     infected(std::vector<state>(edges.size(), Healthy)) {}

void Graph::infectNode(int nodeInd) {
    if (infected[nodeInd] == Healthy)
        infected[nodeInd] = Contaminated;
    else
        infected[nodeInd] = Infected;
}

bool Graph::isInfected(int nodeInd) {
    return (infected[nodeInd] == Contaminated || infected[nodeInd] == Infected);
}

bool Graph::allInfected() {
    //returns True only if the whole graph is infected
    for (state node:infected)
        if (node == Healthy || node == Contaminated)
            return false;
    return true;
}

void Graph::disconnectNode(int chosenNode) {
    for (int i = 0; i < (int) edges.size(); i++) {
        edges[chosenNode][i] = 0;
        edges[i][chosenNode] = 0;
    }
}

const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}

const std::vector<state> &Graph::getInfected() const {
    return infected;
}
/*
private:
    std::vector<std::vector<int>> edges;
    std::vector<state> infected;}
 */
