#pragma once
#include <vector>

class Simulation;

using std::vector;

class JoinPolicy {
    public:
        virtual const int Select(vector<int> &incomingOffers, Simulation &sim) const = 0; // pure virtual function
        virtual ~JoinPolicy() = default;
        virtual JoinPolicy* clone() const = 0; // pure virtual function
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual const int Select(vector<int> &incomingOffers, Simulation &sim) const;
        virtual JoinPolicy* clone() const;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual const int Select(vector<int> &incomingOffers, Simulation &sim) const;
        virtual JoinPolicy* clone() const;
};