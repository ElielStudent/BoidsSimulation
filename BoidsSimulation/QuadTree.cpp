#include "QuadTree.h"

QuadTree::QuadTree() {
	this->boundary = { 0,0,WIDTH,HEIGHT };
	tLeft = bLeft = tRight = bRight = NULL;
	this->capacity = QUADCAPACITY;
}

QuadTree::QuadTree(Rectangle boundary){
	this->boundary = boundary;
	tLeft = bLeft = tRight = bRight = NULL;
	this->capacity = QUADCAPACITY;
}
