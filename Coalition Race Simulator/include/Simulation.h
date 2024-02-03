#pragma once
#include <vector>
#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"
using std::string;
using std::vector;

class Party;

class Simulation
{
    public:
        Simulation(Graph g, vector<Agent> agents);

        void step();
        bool shouldTerminate() const;

        const Graph &getGraph() const;
        const vector<Agent> &getAgents() const;
        const Party &getParty(int partyId) const;
        const int getJoinedCounter() const;
        vector<Party> &getUnJoinedNeighbors(int partyId, vector<Party> &relevantNeighbors) const;
        const int getCoalitionIndex(int agentId) const;
        void addAgent(const Agent &ag); 
        vector<Party> &getVectorParties();
        vector<Coalition> &getVectorCoalitions();
        const vector<vector<int>> getPartiesByCoalitions() const;


    private:
        Graph mGraph;
        vector<Agent> mAgents;
        int joinedStateCounter; // number of parties in 'joined' state
        vector<Coalition> listOfCoalitions = {}; // vector which consists of Coalition objects
};