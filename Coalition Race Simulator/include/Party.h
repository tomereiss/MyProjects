#pragma once
#include <string>
#include <vector>
#include "JoinPolicy.h"
#include "Coalition.h"

class Simulation;

using std::string;
using std::vector;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    virtual ~Party(); // dtor
    Party(const Party &other); // copy ctor
    Party(Party &other); // move ctor
    const Party& operator=(const Party& other); // assingment operator
    const Party& operator=(Party& other); // move assingment operator
    int getId() const;
    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    void addOffer(int coalitionId);

private:
    int mId; // party ID
    string mName; // party name
    int mMandates; // number of mandates
    JoinPolicy *mJoinPolicy; // pointer for JoinPolicy
    State mState; // party state
    vector<int> incomingOffers = {}; // vector for storing incoming offers
    int timer; // timer of party
};
