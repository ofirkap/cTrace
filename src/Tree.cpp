#include "../include/Tree.h"

//Constructor
Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree *>()) {}

//Destructor
void Tree::clear() {
    if (!children.empty())
        for (auto child: children)
            delete child;
}

//Destructor
Tree::~Tree() {
    clear();
}

//copy Constructor
Tree::Tree(const Tree &other) : node(other.node), children() {
    for (auto i : other.children) {
        Tree *curr = i->clone();
        children.push_back(curr);
    }
}

//copy assignment operator
Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        node = other.node;
        clear();
        for (auto i : other.children) {
            Tree *curr = i->clone();
            children.push_back(curr);
        }
    }
    return *this;
}

//move Constructor
Tree::Tree(Tree &&other) : node(other.node), children(other.children) {
    other.children.clear();
}

//move assignment operator
Tree &Tree::operator=(Tree &&other) {
    if (this != &other) {
        node = other.node;
        clear();
        children = other.children;
        other.children.clear();
    }
    return *this;
}

void Tree::addChild(const Tree &child) {
    Tree *clone_child = child.clone();
    children.push_back(clone_child);
}

void Tree::addChild(Tree *child) {
    children.push_back(child);
}

int Tree::getRootLabel() const {
    return node;
}

vector<Tree *> &Tree::getChildren() {
    return children;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    switch (session.getTreeType()) {
        case Root:
            return new RootTree(rootLabel);
        case Cycle:
            return new CycleTree(rootLabel, session.getCurrCycle());
        case MaxRank:
            return new MaxRankTree(rootLabel);
    }
    return nullptr;
}

Tree *Tree::BFS(const Session &session) {
    vector<bool> visited(session.gSize(), 0);
    queue<Tree *> trail;
    trail.push(this);
    visited[this->node] = true;
    while (!trail.empty()) {
        Tree *curr = trail.front();
        trail.pop();
        for (int i = 0; i < session.gSize(); i++) {
            if (session.getG().getEdges()[curr->getRootLabel()][i] == 1 && !visited[i]) {
                Tree *child = createTree(session, i);
                curr->addChild(child);
                trail.push(child);
                visited[i] = true;
            }
        }
    }
    return this;
}


//-------Cycle Tree--------

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

CycleTree *CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    Tree *currNode = this;
    int cycle = currCycle;
    while (cycle != 0 && !currNode->getChildren().empty()) {
        currNode = currNode->getChildren().at(0);
        cycle--;
    }
    return currNode->getRootLabel();
}

//-------Max Rank Tree--------

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

MaxRankTree *MaxRankTree::clone() const {

    return new MaxRankTree(*this);
}

int MaxRankTree::traceTree() {
    //if the tree has no children we will trace the root
    if (getChildren().empty())
        return this->getRootLabel();
    int maxRank = 0;
    int indexMaxRank;
    std::queue<Tree *> trail;
    trail.push(this);
    while (!trail.empty()) {
        Tree *temp = trail.front();
        trail.pop();
        int currRank = temp->getChildren().size();
        int currNode = temp->getRootLabel();
        if (currRank > maxRank) {
            maxRank = currRank;
            indexMaxRank = currNode;
        }
        for (int i = 0; i < currRank; ++i) {
            trail.push(temp->getChildren().at(i));
        }
    }
    return indexMaxRank;
}

//-------Root Tree--------
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return getRootLabel();
}