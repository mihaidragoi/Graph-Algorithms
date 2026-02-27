#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include "edge.h"
#include <vector>
#include <map>

class Graph
{
protected:
    std::vector<Node*> m_nodes;
    std::vector<Edge*> m_edges;


public:
    Graph();
    void addNode(Node* node);
    void addEdge(Node* first, Node* second, double cost);
    std::vector<Node*> getNodes();
    std::vector<Edge*> getEdges();

    bool findAugmentingPath(Node* source, Node* sink, std::map<Node*, Edge*>& parentEdge);
    double updateMaxFlow(Node* source, Node* sink);
    void calculateMinCut(Node* source);
    void resetFlow();
};

#endif // GRAPH_H
