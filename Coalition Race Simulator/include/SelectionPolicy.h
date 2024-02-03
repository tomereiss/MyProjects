#pragma once
#include <vector>
using std::vector;
class Graph;
class Party;

class SelectionPolicy { 
    public:
        virtual const int Select(vector<Party> &optionalPartners, const Graph &graph, int partyId) const = 0;
        virtual SelectionPolicy* clone() const = 0;
        virtual int returnPolicy() const = 0;
        virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
        virtual const int Select(vector<Party> &optionalPartners, const Graph &graph, int partyId) const;
        virtual SelectionPolicy* clone() const;
        virtual int returnPolicy() const;
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
        virtual const int Select(vector<Party> &optionalPartners, const Graph &graph, int partyId) const;
        virtual SelectionPolicy* clone() const;
        virtual int returnPolicy() const;
};