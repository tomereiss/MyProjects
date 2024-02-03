#pragma once
#include <vector>

#include "SelectionPolicy.h"
class Simulation;

class Agent
{
    public:
        Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
        virtual ~Agent(); // dtor
        Agent(const Agent &other); // copy ctor
        Agent(Agent &other); // move ctor
        const Agent& operator=(const Agent& other); // assignment operator
        const Agent& operator=(Agent& other); // move assignment operator
        int getPartyId() const;
        int getId() const;
        SelectionPolicy* getPolicy() const;
        void step(Simulation &sim);

    private:
        int mAgentId; // agent ID
        int mPartyId; // party ID
        SelectionPolicy *mSelectionPolicy; // Pointer to SelectionPolicy
};
