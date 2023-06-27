#pragma once

#include "Point.h"
#include <vector>

struct Data {
    Point pos;
    string city;
    string country;
    int population;

    Data(Point _pos, string _city, string _country, int _data){
        pos = _pos;
        population = _data;
        city = _city;
        country = _country;
    }
    Data(){
        population = 0;
    }
};

class Node{
    private:
        Point topLeft;
        Point botRight;
        vector<Data> d;

        Node *topLeftTree;
        Node *topRightTree;
        Node *botLeftTree;
        Node *botRightTree;
    public:
        Node (Point _topLeft, Point _botRight);
        Node();
        bool insert (Point _p, string _city, string country, int _data);
        int countNodes();
        vector <Data> list();
        bool isLeaf();
        void subdivide();
        bool inBoundary(Point _p);
        void print(Node* node, string indent, int branch);
};
