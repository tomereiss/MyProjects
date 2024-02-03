#pragma once
#include <vector>
#include "SelectionPolicy.h"

using std::vector;

class Party;

class Coalition
{
    public: 
        Coalition(int id, int numMandates, int selectionPolicy,int partyId, int notPossibleId);
        int getNumOfMandates() const;
        const vector<int> &getMembers() const; // get coalition members by id
        void addOffer(const int partyId); // for agent usage
        bool isMember(int partyId) const;
        bool isRelevant(int partyId) const;
        void acceptOffer(int id, int mandates); // for party usage
        int getCoalitionPolicy() const;
        const int getCoalitionId() const;
        

    private:
        int id; // coalition ID
        int numOfMandates; // total number of mandates in colaition
        int coalitionPolicy; // "1" is MandatesPolicy, "0" is EdgeWeightPolicy
        vector<int> coalitionMembers; // id's of parties inside the coalition
        vector<int> coalitionOffers = {}; // id's of already offered parties by the coalition

};