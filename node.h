#ifndef NODE_H
#define NODE_H
#include <QPoint>

class Node
{
protected:
    int m_index;
    QPoint m_coord;

public:
    Node();
    Node(int index, QPoint p);
    void setIndex(int index);
    int getIndex();
    void setCoord(QPoint p);
    QPoint getCoord();
    double getX();
    double getY();
};

#endif // NODE_H
