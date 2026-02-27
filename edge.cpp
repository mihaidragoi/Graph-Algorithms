#include "edge.h"

Edge::Edge():m_first(nullptr), m_second(nullptr), m_cost(0) {}

Edge::Edge(Node *first, Node *second, double cost): m_first(first), m_second(second), m_cost(cost)
{

}

void Edge::setFirst(Node *node)
{
    m_first=node;
}

Node *Edge::getFirst()
{
    return m_first;
}

void Edge::setSecond(Node *node)
{
    m_second=node;
}

Node *Edge::getSecond()
{
    return m_second;
}

void Edge::setCost(double cost)
{
    m_cost=cost;
}

double Edge::getCost()
{
    return m_cost;
}

void Edge::setFlow(double flow)
{
    m_flow = flow;
}

double Edge::getFlow()
{
    return m_flow;
}

double Edge::getResidualCapacity()
{
    return m_cost-m_flow;
}

void Edge::setIsMinCut(bool isCut)
{
    m_isMinCut= isCut;
}

bool Edge::getIsMinCut()
{
    return m_isMinCut;
}
