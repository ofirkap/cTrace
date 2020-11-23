#include "../include/Session.h"
#include "../include/Agent.h"

Session::Session(const std::string &path) : g(vector<vector<int>>()), treeType(), agents(),
                                            infected(queue<int>()), currCycle(-1) {
    ifstream file(path);
    json j;
    file >> j;
    g = Graph(j["graph"]);

    string tree = j["tree"];
    if (tree == "M")
        treeType = MaxRank;
    else if (tree == "C")
        treeType = Cycle;
    else if (tree == "R")
        treeType = Root;
    else
        cout << "Invalid tree type" << endl;

    for (pair<string, int> a:j["agents"]) {
        if (a.first == "V")
            agents.push_back(new Virus(a.second));
        else
            agents.push_back(new ContactTracer());
    }
}

//Destructor
Session::~Session() {
    for (auto &agent : agents)
        if (agent != nullptr)
            delete (agent);
    agents.clear();
}

//Copy Constructor
Session::Session(const Session &other) : g(other.getG()), treeType(other.getTreeType()), agents(),
                                         infected(other.getInfected()), currCycle(other.getCurrCycle()) {
    for (auto agent : other.agents)
        agents.push_back(agent->clone());
}

//Copy Assignment Operator
Session &Session::operator=(const Session &other) {
    if (this != &other) {
        g = other.getG();
        treeType = other.getTreeType();
        agents.clear();
        for (auto agent : other.agents)
            agents.push_back(agent->clone());
        infected = other.getInfected();
        currCycle = other.getCurrCycle();
    }
    return *this;
}

//Move Constructor
Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents),
                                    infected(other.infected), currCycle(other.currCycle) {
    other.agents.clear();
}

//Move Assignment Operator
Session &Session::operator=(Session &&other) {
    if (this != &other) {
        g = other.g;
        treeType = other.treeType;
        agents = other.agents;
        other.agents.clear();
        infected = other.infected;
        currCycle = other.currCycle;
    }
    return *this;
}

void Session::simulate() {
    /*
    before starting the simulation contaminate all nodes with starting viruses
    to ensure a virus doesnt spread to a node with another virus in the first round
    */
    for (auto &agent : agents)
        agent->act(*this);

    currCycle++;
    int size = 0;
    while (!g.allInfected() && size != (int) agents.size()) {
        size = agents.size();
        for (int i = 0; i < size; i++) {
            agents[i]->act(*this);
        }
        currCycle++;
    }
    json j;
    j["graph"] = g.getEdges();
    vector<int> infectedNodes;
    for (int i = 0; i < gSize(); i++) {
        if (g.isInfected(i))
            infectedNodes.push_back(i);
    }
    j["infected"] = infectedNodes;
    ofstream file("./output.json");
    file << j;
}

void Session::addAgent(const Agent &agent) {
    Agent *clone = agent.clone();
    agents.push_back(clone);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int node) {
    infected.push(node);
}

int Session::dequeueInfected() {
    if (!infected.empty()) {
        int temp = infected.front();
        infected.pop();
        return temp;
    } else
        return -1;
}

TreeType Session::getTreeType() const {
    return treeType;
}

Graph Session::getG() const {
    return g;
}

Graph &Session::changeG() {
    return g;
}

int Session::gSize() const {
    return g.getEdges().size();
}

int Session::getCurrCycle() const {
    return currCycle;
}

const queue<int> &Session::getInfected() const {
    return infected;
}

/*

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
    int currCycle = 1;
*/
