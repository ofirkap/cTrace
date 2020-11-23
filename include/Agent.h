#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Tree.h"

class Agent {
public:
    Agent();

    virtual Agent * clone() const = 0;

    virtual void act(Session& session) = 0;

    virtual ~Agent();

};

class ContactTracer : public Agent {
public:
    ContactTracer();

    virtual ContactTracer *clone() const;

    virtual void act(Session& session);

};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    virtual Virus *clone() const;

    virtual void act(Session& session);

private:
    const int nodeInd;
    bool firstTime;
};

#endif