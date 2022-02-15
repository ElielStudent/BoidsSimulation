#include "QuadTree.h"

bool inBounds(FloatRect boundary, Vector2f point) {	//Checks whether a point is in the rectangle bound
	return point.x >= boundary.left && point.x <= boundary.left + boundary.width &&
		point.y >= boundary.top && point.y <= boundary.top + boundary.height;
}

QuadTree::QuadTree() {
	this->boundary = { 0,0,GWIDTH, GHEIGHT };
	this->level = 0;
	this->capacity = QUADCAPACITY;
	this->isDivided = false;
	subNodes[0] = subNodes[1] = subNodes[2] = subNodes[3] = nullptr;
}

QuadTree::QuadTree(int level, FloatRect boundary) {
	this->boundary = boundary;
	this->level = level;
	this->capacity = QUADCAPACITY;
	this->isDivided = false;
	subNodes[0] = subNodes[1] = subNodes[2] = subNodes[3] = nullptr;
}

void QuadTree::SubDivide() {
	Vector2f center = { boundary.left + (boundary.width / 2),boundary.top + (boundary.height / 2) };
	Vector2f size = { boundary.width / 2, boundary.height / 2 };
	//Divides the 4 children
	subNodes[0] = new QuadTree(this->level + 1, FloatRect(boundary.left, boundary.top, size.x, size.y));	//TL
	subNodes[1] = new QuadTree(this->level + 1, FloatRect(center.x, boundary.top, size.x, size.y));			//TR
	subNodes[2] = new QuadTree(this->level + 1, FloatRect(boundary.left, center.y, size.x, size.y));		//BL
	subNodes[3] = new QuadTree(this->level + 1, FloatRect(center.x, center.y, size.x, size.y));				//BR
	isDivided = true;
}

bool QuadTree::Insert(Boid* boid) {
	Vector2f boidPos = boid->getPosition();
	if (!boundary.contains(boidPos))				//If the boid's position belongs in qt
		return false;
	if (!this->isDivided) {							//If it isnt divided,insert into list and divide if necessary
		this->boids.push_back(boid);
		capacity--;
		if (capacity == 0)
			SubDivide();
		return true;
	}

	//Attempts to insert into the sub qts
	for (QuadTree* subNode : subNodes) {
		if (subNode->Insert(boid))
			return true;
	}
	return false;		//Should never happen, failed to insert the boid
}

void QuadTree::Draw(RenderWindow& window) {
	if (!isDivided)return;
	Vector2f center = { boundary.left + (boundary.width / 2),boundary.top + (boundary.height / 2) };
	Vertex vLine[2];			//Vertical line
	Vertex hLine[2];			//Horizontal line
	vLine[0].position = Vector2f(center.x, this->boundary.top);
	vLine[1].position = Vector2f(center.x, this->boundary.top + this->boundary.height);
	hLine[0].position = Vector2f(this->boundary.left, center.y);
	hLine[1].position = Vector2f(this->boundary.left + this->boundary.width, center.y);
	vLine[0].color = Color::Black;
	vLine[1].color = Color::Black;
	hLine[0].color = Color::Black;
	hLine[1].color = Color::Black;
	window.draw(vLine, 2, PrimitiveType::Lines);
	window.draw(hLine, 2, PrimitiveType::Lines);

	if (!isDivided)return;
	for (QuadTree* children : this->subNodes)
		children->Draw(window);
}

void QuadTree::Query(FloatRect boundary,list<Boid*>* boidList) {		//FINISH QUERYING NEARBY
	if (!boundary.intersects(boundary))					//If the boundary is not inside the area
		return;

	for (Boid* b : this->boids) {
		if (inBounds(boundary, b->getPosition()))
			boidList->push_back(b);						//Add boids that are inside
	}

	if (!isDivided)										//If it hasnt been divided dont check children
		return;

	this->subNodes[0]->Query(boundary, boidList);
	this->subNodes[1]->Query(boundary, boidList);
	this->subNodes[2]->Query(boundary, boidList);
	this->subNodes[3]->Query(boundary, boidList);
}

void QuadTree::Clear() {
	boids.clear();
	if (isDivided) {
		for (QuadTree* qt : subNodes) {
			qt->Clear();
			delete qt;
			qt = nullptr;
		}
	}
	isDivided = false;
	this->capacity = QUADCAPACITY;
}