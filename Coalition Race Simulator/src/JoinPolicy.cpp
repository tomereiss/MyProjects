#include "JoinPolicy.h"
#include "Simulation.h"

const int MandatesJoinPolicy::Select(vector<int> &incomingOffers, Simulation &sim) const 
{
	// Choosing for the coalition based on number of mandates
    int preferredCoalition=0; 
    int maxVal=0;
    
    vector<Coalition> &coalitions = sim.getVectorCoalitions();
    for(unsigned int i=0; i < incomingOffers.size(); i++){
        int temp = coalitions[incomingOffers[i]].getNumOfMandates();
        if(temp > maxVal){
            maxVal = temp;
            preferredCoalition = i;
        }
    }
    return preferredCoalition;
}

JoinPolicy* MandatesJoinPolicy::clone() const 
{
	// cloning using polymorphism
    return new MandatesJoinPolicy();
}

const int LastOfferJoinPolicy::Select(vector<int> &incomingOffers, Simulation &sim) const 
{
	// choosing the coalition based on last offer
    return incomingOffers.size()-1;
}

JoinPolicy* LastOfferJoinPolicy::clone() const 
{
	// cloning using polymorphism
    return new LastOfferJoinPolicy();
}