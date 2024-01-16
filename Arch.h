#pragma once
#include "Node.h"

class Arch
{
public:
    Arch(int nodeFrom, int nodeTo, int capacity);

    int GetFlow() const;
    
    QString GetArchData() const;

    void UpdateFlow(int minCapacity);

    int GetNodeTo() const;

    int GetNodeFrom() const;

    int GetReverseEdgeIndex() const;

    bool HasPositiveResidualCapacity() const;

    int UpdateMinCapacity(int minCapacity) const;
    
    int GetCapacity() const;

    void ResetFlow();

private:
    int m_nodeTo;          // Nodul de destinație al arcului
    int m_capacity;    // Capacitatea arcului
    int m_flow;        // Fluxul curent pe arc
    int m_nodeFrom; // Indexul arcului invers in graf 

};


