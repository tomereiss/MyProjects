#include "Party.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), incomingOffers() ,timer(0)
{
}

Party::~Party() // dtor
{
    if(mJoinPolicy) delete mJoinPolicy;
}

Party::Party(const Party &other): mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy->clone()),mState(other.mState),incomingOffers(other.incomingOffers),timer(other.timer)
{
	//copy ctor
}

Party::Party(Party &other):mId(other.mId),mName(other.mName),mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy),mState(other.mState),incomingOffers(other.incomingOffers),timer(other.timer)
{
     //move ctor
	other.mJoinPolicy = nullptr;
}

const Party& Party::operator=(const Party& other)  // assingment operator 
{
    if(this != &other){
        delete mJoinPolicy;
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy->clone();
        mState = other.mState;
        incomingOffers = other.incomingOffers;
        timer = other.timer;
    }
    return *this;
}
const Party& Party::operator=(Party& other) // move assingment operator
{
    if(mJoinPolicy) delete mJoinPolicy;
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    mState = other.mState;
    incomingOffers = other.incomingOffers;
    timer = other.timer;

    other.mJoinPolicy = nullptr;

    return *this;
}

int Party::getId() const
{
    return mId;
}

State Party::getState() const // returns party state
{
    return mState;
}

void Party::setState(State state) // set party state
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if(timer == 3){ // Making a decision
        int indexChosen = mJoinPolicy->Select(incomingOffers,s); //choosing the right coalition
        vector<Coalition> &coalitions = s.getVectorCoalitions(); // vector of all coalitions
        int chosenCoalitionId = incomingOffers[indexChosen]; // coalition ID
        coalitions[chosenCoalitionId].acceptOffer(mId,mMandates); // Updating the coalition that we joined them
        setState(Joined); // changing state to 'joined'

        if (coalitions[chosenCoalitionId].getCoalitionPolicy() == 1) 
			// Cloning an agent and increasing joinedStateCounter
            s.addAgent(Agent(s.getJoinedCounter(), mId, new MandatesSelectionPolicy)); 
        else // Cloning an agent and increasing joinedStateCounter
            s.addAgent(Agent(s.getJoinedCounter(), mId, new EdgeWeightSelectionPolicy)); 
    }
    else if(timer!=0) // Still CollectingOffers
        timer += 1;
}

void Party::addOffer(int coalitionId)
{
    if(mState == Waiting){ //Starting the timer as it is the first offer and chaging state
        setState(CollectingOffers);
        timer++;
    } 
    incomingOffers.push_back(coalitionId); // adding the offer to offers vector
}