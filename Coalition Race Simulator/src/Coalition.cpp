#include "Coalition.h"
#include "Party.h"

Coalition::Coalition(int id, int numMandates, int selectionPolicy, int partyId, int notPossibleId) : id(id), numOfMandates(numMandates), coalitionPolicy(selectionPolicy), coalitionMembers({partyId}), coalitionOffers()
{
}

int Coalition::getNumOfMandates() const // returns total number of mandates in coalition
{
    return numOfMandates;
}

const vector<int> &Coalition::getMembers() const // returns const reference to vector of party ID's which are part of coalition
{
    return coalitionMembers;
}

void Coalition::addOffer(const int partyId)  // adds the offered partyId to coalitionOffers vector
{
    coalitionOffers.push_back(partyId);
}

bool Coalition::isMember(int partyId) const // returns true if the party is part of the coalition
{
    for(unsigned int i=0; i<coalitionMembers.size();i++){
        if(coalitionMembers[i] == partyId)
            return true;
    }
    return false;
}

bool Coalition::isRelevant(int partyId) const  // returns true if our agents haven't offered the party
{
    for(unsigned int i=0; i<coalitionOffers.size(); i++){
        if(coalitionOffers[i] == partyId)
            return false;
    }
    return true;
}

void Coalition::acceptOffer(int id, int mandates) // Party is updating the coalition about the joining
{
    coalitionMembers.push_back(id);
    numOfMandates += mandates;
}

int Coalition::getCoalitionPolicy() const // "1" stands for MandatesPolicy and "0" for EdgeWeightPolicy
{
    return coalitionPolicy;
} 
const int Coalition::getCoalitionId() const // returns id of coalition
{
    return id;
}

