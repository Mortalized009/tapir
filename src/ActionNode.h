#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <queue>

#include "Observation.h"
#include "Model.h"

class BeliefNode;

class ActionNode {
public:
    friend class BeliefNode;

    ActionNode(long actId, ObsVals &obs, BeliefNode *nxtBelNode);
    ActionNode(long actId, long nParticles, double qVal, double avgQVal);
    ~ActionNode();

    void updateQVal(double newVal);
    void updateQVal(double prevVal, double newVal, bool reduceParticles);
    bool isAct(long aIdx);
    void addChild(ObsVals &obs, BeliefNode* nxtBelNode);
    BeliefNode* getObsChild(ObsVals &obs);
    void getChildren(std::queue<BeliefNode*> &res);
    void delParticle(double delVal);
    void write(std::ostream &os);
    void writeNGetChildren(std::ostream &os, std::queue<BeliefNode*> &res);

    inline double getQVal() {
        return qVal;
    }

private:
    long actId, nParticles;
    double qVal, avgQVal;

    std::vector<Observation*> obsChildren;

};
#endif