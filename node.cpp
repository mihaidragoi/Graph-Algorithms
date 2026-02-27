#include "node.h"

Node::Node():m_index(0), m_coord(0,0) {}

Node::Node(int index, QPoint p): m_index(index), m_coord(p)
{

}

void Node::setIndex(int index)
{
    m_index=index;
}

int Node::getIndex()
{
    return m_index;
}

void Node::setCoord(QPoint p)
{
    m_coord=p;
}

QPoint Node::getCoord()
{
    return m_coord;
}

double Node::getX()
{
    return m_coord.x();
}

double Node::getY()
{
    return m_coord.y();
}
