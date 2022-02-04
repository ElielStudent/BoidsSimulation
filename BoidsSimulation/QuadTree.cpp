#include "QuadTree.h"

QuadTree::QuadTree() {
	this->boundary = { 0,0,GWIDTH, GHEIGHT};
	tLeft = bLeft = tRight = bRight = NULL;
	this->capacity = QUADCAPACITY;
}

QuadTree::QuadTree(IntRect boundary){
	this->boundary = boundary;
	tLeft = bLeft = tRight = bRight = NULL;
	this->capacity = QUADCAPACITY;
}
