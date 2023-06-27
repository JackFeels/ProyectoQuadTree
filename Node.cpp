#include "Node.h"
#include <cmath>

Node::Node(Point _topLeft, Point _botRight){
    topLeft = _topLeft;
    botRight = _botRight;
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
}
Node::Node(){
    topLeft = Point(0, 0);
    botRight = Point(0, 0);
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
}

bool Node::insert(Point _p, string _city, string _country, int _population)
{
    //cout << "Intentando insertar: " << _city << " en (" << _p.x << ", " << _p.y << ")" << endl;

    // Verificar si el punto está dentro de los límites
    if (!inBoundary(_p))
    {
        //cout << "Punto fuera de los límites." << endl;
        return false;
    }

    //cout << "Punto dentro de los límites." << endl;

    // Si el tamaño de la región es suficientemente pequeño, almacenar el punto en este nodo
    if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1)
    {
        //cout << "Almacenando punto en este nodo." << endl;
        d.push_back(Data(_p, _city, _country, _population));
        return true;
    }

    //cout << "Subdividiendo el nodo." << endl;

    // Calcular las coordenadas del punto medio
    double midX = (topLeft.x + botRight.x) / 2.0;
    double midY = (topLeft.y + botRight.y) / 2.0;

    // Determinar en qué cuadrante del nodo actual debería ir el punto e insertarlo recursivamente
    if (_p.x <= midX)
    {
        // Punto está en la mitad izquierda
        if (_p.y <= midY)
        {
            // Punto está en la parte inferior izquierda
            if (botLeftTree == nullptr)
            {
                //cout << "Creando nuevo nodo inferior izquierdo." << endl;
                botLeftTree = new Node(Point(topLeft.x, midY), Point(midX, botRight.y));
            }
            return botLeftTree->insert(_p, _city, _country, _population);
        }
        else
        {
            // Punto está en la parte superior izquierda
            if (topLeftTree == nullptr)
            {
                //cout << "Creando nuevo nodo superior izquierdo." << endl;
                topLeftTree = new Node(topLeft, Point(midX, midY));
            }
            return topLeftTree->insert(_p, _city, _country, _population);
        }
    }
    else
    {
        // Punto está en la mitad derecha
        if (_p.y <= midY)
        {
            // Punto está en la parte inferior derecha
            if (botRightTree == nullptr)
            {
                //cout << "Creando nuevo nodo inferior derecho." << endl;
                botRightTree = new Node(Point(midX, midY), botRight);
            }
            return botRightTree->insert(_p, _city, _country, _population);
        }
        else
        {
            // Punto está en la parte superior derecha
            if (topRightTree == nullptr)
            {
                //cout << "Creando nuevo nodo superior derecho." << endl;
                topRightTree = new Node(Point(midX, topLeft.y), Point(botRight.x, midY));
            }
            return topRightTree->insert(_p, _city, _country, _population);
        }
    }
}


void Node::subdivide() {
    double midX = (topLeft.x + botRight.x) / 2.0;
    double midY = (topLeft.y + botRight.y) / 2.0;

    topLeftTree = new Node(topLeft, Point(midX, midY));
    topRightTree = new Node(Point(midX, topLeft.y), Point(botRight.x, midY));
    botLeftTree = new Node(Point(topLeft.x, midY), Point(midX, botRight.y));
    botRightTree = new Node(Point(midX, midY), botRight);
}


bool Node::isLeaf() {
    return (topLeftTree == NULL && topRightTree == NULL && botLeftTree == NULL && botRightTree == NULL);
}
bool Node::inBoundary(Point p) {
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y <= topLeft.y && p.y >= botRight.y);
}

int Node::countNodes() {
    int count = 1; // Contar este nodo

    // Sumar el recuento de los nodos hijos, si existen
    if (topLeftTree != NULL) {
        count += topLeftTree->countNodes();
    }
    if (topRightTree != NULL) {
        count += topRightTree->countNodes();
    }
    if (botLeftTree != NULL) {
        count += botLeftTree->countNodes();
    }
    if (botRightTree != NULL) {
        count += botRightTree->countNodes();
    }

    return count;
}

vector<Data> Node::list(){
    vector<Data> cities;
    if (!isLeaf())
    {
        if (topLeftTree != NULL)
        {
            vector<Data> data_tl = topLeftTree->list();
            cities.insert(cities.end(), data_tl.begin(), data_tl.end());
        }
        if (topRightTree != NULL)
        {
            vector<Data> data_tr = topRightTree->list();
            cities.insert(cities.end(), data_tr.begin(), data_tr.end());
        }
        if (botLeftTree != NULL)
        {
            vector<Data> data_bl = botLeftTree->list();
            cities.insert(cities.end(), data_bl.begin(), data_bl.end());
        }
        if (botRightTree != NULL)
        {
            vector<Data> data_br = botRightTree->list();
            cities.insert(cities.end(), data_br.begin(), data_br.end());
        }
    }
    return cities;
}
void Node::print(Node* node, string indent, int branch){
    if (node != NULL) {
        cout << indent;
        if (branch == 0) {
            cout << "TL----";
            indent += "|  ";
        }
        else if (branch == 1) {
            cout << "TR----";
            indent += "|  ";
        }
        else if (branch == 2) {
            cout << "BL----";
            indent += "|  ";
        }
        else if (branch == 3) {
            cout << "BR----";
            indent += "|  ";
        }

        if (node->d.empty()) {
            cout << "X" << endl;
        }
        else {
            cout << node->d[0].city << " + " << node->d.size() - 1 << " other cities" << endl;
        }

        print(node->topLeftTree, indent, 0);
        print(node->topRightTree, indent, 1);
        print(node->botLeftTree, indent, 2);
        print(node->botRightTree, indent, 3);
    }
}