#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

vector<Party> &Graph::getUnJoinedNeighbors(int partyId, vector<Party> &relevantNeighbors) const
{
    // returning vector of party's relevant neighbors (neighbors that aren't 'joined')
    for(int i=0; i<getNumVertices(); i++){
        if(getEdgeWeight(i,partyId) > 0){
            if(mVertices[i].getState() != Joined)
                relevantNeighbors.push_back(mVertices[i]);
        }
    }
    return relevantNeighbors;
}

vector<Party> &Graph::getVertices()
{
    return mVertices;
}