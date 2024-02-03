#include "Simulation.h"
#include "Party.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), joinedStateCounter(mAgents.size()), listOfCoalitions()
{
    for (unsigned int i=0;i<mAgents.size();i++){ // builiding coalitions vector
        int partyId = mAgents[i].getPartyId();
        int selectionPolicy = mAgents[i].getPolicy()->returnPolicy();
        const vector<Party> &parties = mGraph.getVertices();         // dtor is taking action ??
        listOfCoalitions.push_back(Coalition(i, parties[partyId].getMandates(), selectionPolicy, partyId, -1)); 
    }
}

void Simulation::step()
{
    if(!shouldTerminate()){ // checking if the program should be terminated
        vector<Party> &parties = mGraph.getVertices(); 
        for(int i =0;i<mGraph.getNumVertices();i++){ // parties step loop
            if(parties[i].getState() != Joined){
                parties[i].step(*this);
            }
        }
        for(unsigned int i=0;i<mAgents.size();i++){ // agents step loop
            mAgents[i].step(*this);
        }
    }
}

bool Simulation::shouldTerminate() const
{
    if(getJoinedCounter() == getGraph().getNumVertices()) // checking if all the parties are in 'joined' state
        return true;

    for(unsigned int i=0;i<listOfCoalitions.size();i++){ // check if any coalition has reached 61 mandates
        if(listOfCoalitions[i].getNumOfMandates() > 60) 
            return true;
    }
    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

const int Simulation::getJoinedCounter() const
{
    return joinedStateCounter;
}

vector<Party> &Simulation::getUnJoinedNeighbors(int partyId, vector<Party> &relevantNeighbors) const
{
	// detour function to function of graph
    return mGraph.getUnJoinedNeighbors(partyId,relevantNeighbors);
}

const int Simulation::getCoalitionIndex(int partyId) const
{
    // Searching for the right coalition and returning index (which is the same as coalitionID)
    for(unsigned int i=0; i<listOfCoalitions.size()-1; i++){
        if(listOfCoalitions[i].isMember(partyId)){
            return i;
        }
    }
    return listOfCoalitions.size()-1; // Complexity of size() is constant
}

void Simulation::addAgent(const Agent &ag) // adding an agent to agents vector and increasing joinedStateCounter
{
    joinedStateCounter++;
    mAgents.push_back(ag);    
}

vector<Party> &Simulation::getVectorParties()
{
	// detour function to graph function
    return mGraph.getVertices();
}

vector<Coalition> &Simulation::getVectorCoalitions()
{
	// returning reference to vector listOfCoalitions
    return listOfCoalitions;
}


/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> final; // each element is a vector of party IDs in the coalition.
    for(unsigned int i=0; i<listOfCoalitions.size(); i++){
        const vector<int> &members = listOfCoalitions[i].getMembers();
        final.push_back(members);
    }
    return final;
}

