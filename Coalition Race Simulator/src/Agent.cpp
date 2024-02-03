#include "Agent.h"
#include "Simulation.h"

using namespace std;

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
}

Agent::~Agent() // dtor
{
    if(mSelectionPolicy) delete mSelectionPolicy;
}

Agent::Agent(const Agent &other): mAgentId(other.mAgentId), mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy->clone()) // copy ctor
{
}

Agent::Agent(Agent &other): mAgentId(other.mAgentId),mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy)// move ctor
{
    other.mSelectionPolicy = nullptr;
}

const Agent& Agent::operator=(const Agent& other)  // copy assingment operator 
{
    if(this != &other){
        delete mSelectionPolicy;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy->clone();
    }
    return *this;
}

const Agent& Agent::operator=(Agent& other) // move assingment operator
{
    if(mSelectionPolicy) delete mSelectionPolicy;

    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;

    return *this;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getId() const
{
    return mAgentId;
}

SelectionPolicy* Agent::getPolicy() const
{
    return mSelectionPolicy;
}

void Agent::step(Simulation &sim)
{
    vector<Party> temp;
    vector<Party> &potential = sim.getUnJoinedNeighbors(getPartyId(),temp); // Relevant neighbors of agent's party
    vector<Coalition> &coalitions = sim.getVectorCoalitions();
    int coalitionId = sim.getCoalitionIndex(getPartyId()); // Agent realizes to which coalition he belongs (we couldn't add a field)
    vector<Party> finalList;

    for(unsigned int i=0; i<potential.size(); i++){ // creating a list which avoids duplicate offers from coalition's agents
        if(coalitions[coalitionId].isRelevant(potential[i].getId()))
            finalList.push_back(potential[i]);
    }
    
    int chosenPartyId = mSelectionPolicy->Select(finalList, sim.getGraph(), getPartyId()); // partyId of chosen party

    if(chosenPartyId != -1){
        sim.getVectorParties()[chosenPartyId].addOffer(coalitionId); // offering a party
        coalitions[coalitionId].addOffer(chosenPartyId); // updating the coalition about the offer
    }
}