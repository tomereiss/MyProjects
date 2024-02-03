#include "SelectionPolicy.h"
#include "Party.h"
#include "Graph.h"

const int MandatesSelectionPolicy::Select(vector<Party> &optionalPartners, const Graph &graph, int partyId) const 
{
	// choosing the party based on number of mandates
    if(optionalPartners.size() == 0) return -1; // no offers available
    
    int preferredParty=0;
    int maxVal=0;

    for(unsigned int i=0; i < optionalPartners.size(); i++){
        int temp = optionalPartners[i].getMandates();
        if(temp > maxVal){
            maxVal = temp;
            preferredParty = i;
        }
    }
    return optionalPartners[preferredParty].getId();
}

SelectionPolicy* MandatesSelectionPolicy::clone() const
{
	// cloning in a polymorphic way
    return new MandatesSelectionPolicy;
}

int MandatesSelectionPolicy::returnPolicy() const
{
    return 1; // 1 stands for MandatesSelectionPolicy
}

const int EdgeWeightSelectionPolicy::Select(vector<Party> &optionalPartners, const Graph &graph, int partyId) const 
{
    // choosing the party based on edge weight 
	if(optionalPartners.size() == 0) return -1; // no offers available

    int preferredParty=0;
    int maxWeight=0;

    for(unsigned int i=0; i < optionalPartners.size(); i++){
        int temp = graph.getEdgeWeight(optionalPartners[i].getId(), partyId);
        if(temp > maxWeight){
            preferredParty = i;
            maxWeight = temp;
        }
    }
    return optionalPartners[preferredParty].getId();
}

SelectionPolicy* EdgeWeightSelectionPolicy::clone() const
{
	// cloning in a polymorphic way
    return new EdgeWeightSelectionPolicy;
}

int EdgeWeightSelectionPolicy::returnPolicy() const
{
    return 0; // 0 stands for EdgeWeightSelectionPolicy
}