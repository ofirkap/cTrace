#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <queue>
#include "Session.h"

class Session;

class Tree {
public:
    Tree(int rootLabel);

    Tree(Tree &&other);

    virtual ~Tree();

    //copy constructor
    Tree(const Tree &other);

    //copy assignment operator
    Tree &operator=(const Tree &other);

    //move constructor
    Tree &operator=(Tree &&other);

    virtual Tree *clone() const = 0;

    void clear();

    void addChild(const Tree &child);

    void addChild(Tree *child);

    int getRootLabel() const;

    std::vector<Tree *> &getChildren();

    static Tree *createTree(const Session &session, int rootLabel);

    Tree *BFS(const Session &session);

    virtual int traceTree() = 0;

private:
    int node;
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual CycleTree *clone() const;

    virtual int traceTree();

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual MaxRankTree *clone() const;

    virtual int traceTree();
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual RootTree *clone() const;

    virtual int traceTree();
};

#endif