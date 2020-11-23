#include "../include/Agent.h"

Agent::Agent() {}

Agent::~Agent() {}

//ContactTracer

ContactTracer::ContactTracer() {}

ContactTracer *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    //act on the first node in the infected queue
    //create a BFS tree from it and find the node to disconnect
    int root = session.dequeueInfected();
    //if root == -1 it means that the queue was empty
    if (root != -1) {
        Tree *bfs = Tree::createTree(session, root);
        bfs->BFS(session);
        int chosenNode = bfs->traceTree();
        //disconnect all the neighbours of the node and update the graph in session
        session.changeG().disconnectNode(chosenNode);
        delete(bfs);
    }
}

//Virus

Virus::Virus(int nodeInd) : nodeInd(nodeInd), firstTime(true) {}

Virus *Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session &session) {
    //contaminate the node in the initialization round
    if (session.getCurrCycle() == -1) {
        session.changeG().infectNode(nodeInd);
        return;
    }
    //in the first cycle after the virus creation infect its node and add it to the infected queue
    if (firstTime) {
        session.enqueueInfected(nodeInd);
        session.changeG().infectNode(nodeInd);
        firstTime = false;
    }
    /*
    check the row of the current infected node for his lowest ranked healthy neighbor
    infect it and create a new virus
     */
    for (int i = 0; i < session.gSize(); i++) {
        if (session.getG().getEdges()[nodeInd][i] == 1 && !session.getG().isInfected(i)) {
            session.changeG().infectNode(i);
            session.addAgent(Virus(i));
            return;
        }
    }
}