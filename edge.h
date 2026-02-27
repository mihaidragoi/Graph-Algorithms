#ifndef EDGE_H
#define EDGE_H
#include "node.h"

class Edge
{
protected:
    Node* m_first;
    Node* m_second;
    double m_cost;
    double m_flow = 0;
    bool m_isMinCut;

public:
    Edge();
    Edge(Node* first, Node* second, double cost);
    void setFirst(Node* node);
    Node* getFirst();
    void setSecond(Node* node);
    Node* getSecond();
    void setCost(double cost);
    double getCost();
    void setFlow(double flow);
    double getFlow();
    double getResidualCapacity();
    void setIsMinCut(bool isCut);
    bool getIsMinCut();
};

#endif // EDGE_H
