#pragma once
#include "Node.h"
class QuadTree{
private:
    Node* root;
    int countPoints;

public:
    QuadTree();
    void insert(Point _p, string _city, string _country, int _population);
    int totalNodes();
    int totalPoints();
    vector<Data> list();
    void printQuadTree();
};
