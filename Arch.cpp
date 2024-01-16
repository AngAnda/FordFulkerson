#include "Arch.h"
#include <algorithm>

Arch::Arch(int nodeFrom, int nodeTo, int capacity):
    m_nodeFrom(nodeFrom), // vedem daca pastram
    m_nodeTo(nodeTo),
    m_capacity(capacity),
    m_flow(0)
{
    // empty
}

int Arch::GetFlow() const
{
    return m_flow;
}

QString Arch::GetArchData() const
{
    return QString("sadw");
}

void Arch::UpdateFlow(int minCapacity)
{
    m_flow += minCapacity;
}

int Arch::GetNodeTo() const
{
    return m_nodeTo;
}

int Arch::GetReverseEdgeIndex() const
{
    return m_nodeFrom; // Întoarce indexul arcului invers în graf
}

bool Arch::HasPositiveResidualCapacity() const
{
    return (m_capacity - m_flow) > 0;
}

int Arch::UpdateMinCapacity(int minCapacity) const
{
    return std::min(minCapacity, GetCapacity() - GetFlow());
}

int Arch::GetCapacity() const
{
    return m_capacity;
}
