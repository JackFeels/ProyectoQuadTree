// Adapted from the Original code: https://www.geeksforgeeks.org/quad-tree/ (May 24, 2023)


#include "QuadTree.h"
QuadTree::QuadTree() {
   root = new Node(Point(-180,90), Point(180, -90));
   countPoints = 0;
}
// Insert a node into the quadtree
void QuadTree::insert(Point _p, string _city, string _country, int _population)
{
	if(root->insert(_p,_city,_country,_population)){
		countPoints++;
	}
}
int QuadTree::totalPoints(){
	return countPoints;
}
int QuadTree::totalNodes(){
	return root->countNodes();
}
vector<Data> QuadTree::list(){
	return root->list();
}
void QuadTree::printQuadTree(){
	cout << endl << "*** PRINT QUADTREE ***" << endl << endl;
	root->print(root, "", 0);
}