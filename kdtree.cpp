#include "kdtree.h"

KDTree::KDTree(): root(nullptr) {}

KDTree::~KDTree()
{
    freeTree(root);
}

void KDTree::build(std::vector<Node *> &nodes)
{
    root = buildRecurent(nodes,0);
}

Node *KDTree::nearestNeighbor(double x, double y)
{
    Node* best = nullptr;
    double bestDistance = 1e18;
    nearestRecurent(root,x,y,best,bestDistance);
    return best;
}

void KDTree::nearestRecurent(KDNode *current, double x, double y, Node *&best, double &bestDistance)
{
    if(!current)
        return;

    double dx = current->node->getLatitude() - x;
    double dy = current->node->getLongitude() - y;
    double dist = dx*dx + dy*dy;

    if(dist < bestDistance)
    {
        bestDistance = dist;
        best = current->node;
    }

    KDNode* first;
    KDNode* second;

    if(current->splitX)
    {
        if(x < current->node->getLatitude())
            first = current->left, second = current->right;
        else
            first = current->right, second = current->left;
    }
    else
    {
        if(y < current->node->getLongitude())
            first = current->left, second = current->right;
        else
            first = current->right, second = current->left;
    }

    nearestRecurent(first, x, y, best, bestDistance);

    double diff = current->splitX ? x - current->node->getLatitude() :y - current->node->getLongitude();

    if(diff*diff < bestDistance)
        nearestRecurent(second, x, y, best, bestDistance);
}

void KDTree::freeTree(KDNode *node)
{
    if(!node)
        return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

bool compareLatitude(Node* a, Node* b)
{
    return a->getLatitude() < b->getLatitude();
}

bool compareLongitude(Node* a, Node* b)
{
    return a->getLongitude() < b->getLongitude();
}


KDTree::KDNode *KDTree::buildRecurent(std::vector<Node *> nodes, int depth)
{
    if(nodes.empty())
        return nullptr;

    bool splitX = (depth % 2 == 0);

    if(splitX)
        std::sort(nodes.begin(), nodes.end(), compareLatitude);
    else
        std::sort(nodes.begin(), nodes.end(), compareLongitude);

    int mid = nodes.size() / 2;

    KDNode* node = new KDNode(nodes[mid], splitX);
    node->left = buildRecurent(std::vector<Node*>(nodes.begin(), nodes.begin() + mid), depth + 1);
    node->right = buildRecurent(std::vector<Node*>(nodes.begin() + mid + 1, nodes.end()),depth + 1);

    return node;
}
