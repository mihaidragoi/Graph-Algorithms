#include "graph.h"
#include <queue>

Graph::Graph() {}

void Graph::addNode(Node *node)
{
    m_nodes.push_back(node);
}

void Graph::addEdge(Node *first, Node *second, double cost)
{
    m_edges.push_back(new Edge(first, second, cost));
}

std::vector<Node *> Graph::getNodes()
{
    return m_nodes;
}

std::vector<Edge *> Graph::getEdges()
{
    return m_edges;
}

bool Graph::findAugmentingPath(Node *source, Node *sink, std::map<Node *, Edge *> &parentEdge)
{
    parentEdge.clear();
    std::map<Node*, bool> visited;
    std::queue<Node*> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();
        for (Edge* edge : m_edges)
        {
            if (edge->getFirst() == current && !visited[edge->getSecond()] && edge->getResidualCapacity() > 0)
            {
                visited[edge->getSecond()] = true;
                parentEdge[edge->getSecond()] = edge;
                q.push(edge->getSecond());
                if (edge->getSecond() == sink)
                    return true;
            }
            else if (edge->getSecond() == current && !visited[edge->getFirst()] && edge->getFlow() > 0)
            {
                visited[edge->getFirst()] = true;
                parentEdge[edge->getFirst()] = edge;
                q.push(edge->getFirst());
                if (edge->getFirst() == sink)
                    return true;
            }
        }
    }
    return false;
}

double Graph::updateMaxFlow(Node *source, Node *sink)
{
    std::map<Node*, Edge*> parentEdge;
    if (!findAugmentingPath(source, sink, parentEdge))
        return 0;

    double pathFlow = 1e9;
    Node* current = sink;

    while (current != source)
    {
        Edge* edge = parentEdge[current];
        if (edge->getSecond() == current)
            pathFlow = std::min(pathFlow, edge->getResidualCapacity());
        else
            pathFlow = std::min(pathFlow, edge->getFlow());
        current = (edge->getSecond() == current) ? edge->getFirst() : edge->getSecond();
    }

    current = sink;

    while (current != source)
    {
        Edge* edge = parentEdge[current];
        if (edge->getSecond() == current)
            edge->setFlow(edge->getFlow() + pathFlow);
        else
            edge->setFlow(edge->getFlow() - pathFlow);
        current = (edge->getSecond() == current) ? edge->getFirst() : edge->getSecond();
    }

    return pathFlow;
}

void Graph::calculateMinCut(Node *source)
{
    std::map<Node*, bool> visited;
    std::queue<Node*> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();

        for (Edge* edge : m_edges)
        {
            if (edge->getFirst() == current && !visited[edge->getSecond()] && edge->getResidualCapacity() > 0)
            {
                visited[edge->getSecond()] = true;
                q.push(edge->getSecond());
            }
            if (edge->getSecond() == current && !visited[edge->getFirst()] && edge->getFlow() > 0)
            {
                visited[edge->getFirst()] = true;
                q.push(edge->getFirst());
            }
        }
    }

    for (Edge* edge : m_edges)
    {
        if (visited[edge->getFirst()] && !visited[edge->getSecond()])
            edge->setIsMinCut(true);
        else
            edge->setIsMinCut(false);
    }
}

void Graph::resetFlow()
{
    for (Edge* edge : m_edges)
    {
        edge->setFlow(0);
        edge->setIsMinCut(false);
    }
}
