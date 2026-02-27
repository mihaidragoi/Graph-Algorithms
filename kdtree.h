#ifndef KDTREE_H
#define KDTREE_H
#include "node.h"

class KDTree
{
    struct KDNode{
        Node* node;
        KDNode* left;
        KDNode* right;
        bool splitX;

        KDNode(Node* n, bool s): node(n), left(nullptr), right(nullptr), splitX(s)
        {

        }
    };

private:
    KDNode* root;

public:
    KDTree();
    ~KDTree();
    void build(std::vector<Node*>& nodes);
    Node* nearestNeighbor(double x, double y);
    KDNode* buildRecurent(std::vector<Node*> nodes, int depth);
    void nearestRecurent(KDNode* current, double x, double y, Node*& best, double &bestDistance);
    void freeTree(KDNode* node);
};

#endif // KDTREE_H
