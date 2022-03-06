#include "QuadTree.h"
template class QuadTree<BaseBoid>;

bool inBounds(FloatRect boundary, Vector2f point) {	//True if point is inside, false if its the same point or outside
	if (boundary.left + boundary.width / 2 == point.x && boundary.top + boundary.height / 2 == point.y)
		return false;
	return point.x >= boundary.left && point.x <= boundary.left + boundary.width &&
		point.y >= boundary.top && point.y <= boundary.top + boundary.height;
}

bool CircRectIntersects(FloatRect boundary, Vector2f center, float radius) {
	Vector2f circleDistance;
	circleDistance.x = abs(center.x - (boundary.left+boundary.width/2));
	circleDistance.y = abs(center.y - (boundary.top+boundary.height/2));

	if (circleDistance.x > (boundary.width / 2 + radius)) { return false; }
	if (circleDistance.y > (boundary.height / 2 + radius)) { return false; }

	if (circleDistance.x <= (boundary.width / 2)) { return true; }
	if (circleDistance.y <= (boundary.height / 2)) { return true; }

	float cornerDistance_sq = ((circleDistance.x - boundary.width / 2) * (circleDistance.x - boundary.width / 2)) +
		((circleDistance.y - boundary.height / 2) * (circleDistance.y - boundary.height / 2));

	return (cornerDistance_sq <= (radius * radius));
}

bool inRadius(Vector2f point1, float radius, Vector2f point2) {
	float test = distSqrd(point1, point2);
	return  test != 0 && test <= radius * radius;	//Doesnt include itself in isRadius
	//return distSqrd(point1, point2) <= radius * radius;
}


template<typename T>
QuadTree<T>::QuadTree() {
	this->boundary = { 0,0,GWIDTH, GHEIGHT };
	this->level = 0;
	this->capacity = QUADCAPACITY;
	this->isDivided = false;
	subNodes[0] = subNodes[1] = subNodes[2] = subNodes[3] = nullptr;
}

template<typename T>
QuadTree<T>::QuadTree(int level, FloatRect boundary) {
	this->boundary = boundary;
	this->level = level;
	this->capacity = QUADCAPACITY;
	this->isDivided = false;
	subNodes[0] = subNodes[1] = subNodes[2] = subNodes[3] = nullptr;
}

template<typename T>
void QuadTree<T>::SubDivide() {
	Vector2f center = { boundary.left + (boundary.width / 2),boundary.top + (boundary.height / 2) };
	Vector2f size = { boundary.width / 2, boundary.height / 2 };
	//Divides the 4 children
	subNodes[0] = new QuadTree(this->level + 1, FloatRect(boundary.left, boundary.top, size.x, size.y));	//TL
	subNodes[1] = new QuadTree(this->level + 1, FloatRect(center.x, boundary.top, size.x, size.y));			//TR
	subNodes[2] = new QuadTree(this->level + 1, FloatRect(boundary.left, center.y, size.x, size.y));		//BL
	subNodes[3] = new QuadTree(this->level + 1, FloatRect(center.x, center.y, size.x, size.y));				//BR
	isDivided = true;
}

template<typename T>
bool QuadTree<T>::Insert(T* boid) {
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
	for (QuadTree<T>* subNode : subNodes) {
		if (subNode->Insert(boid))
			return true;
	}
	return false;		//Should never happen, failed to insert the boid
}

template<typename T>
void QuadTree<T>::Draw(RenderWindow& window) {
	if (!isDivided)return;
	Vector2f center = { boundary.left + (boundary.width / 2),boundary.top + (boundary.height / 2) };
	Vertex vLine[2];			//Vertical line
	Vertex hLine[2];			//Horizontal line
	vLine[0].position = Vector2f(center.x, this->boundary.top);
	vLine[1].position = Vector2f(center.x, this->boundary.top + this->boundary.height);
	hLine[0].position = Vector2f(this->boundary.left, center.y);
	hLine[1].position = Vector2f(this->boundary.left + this->boundary.width, center.y);
	vLine[0].color = Color::White;
	vLine[1].color = Color::White;
	hLine[0].color = Color::White;
	hLine[1].color = Color::White;
	window.draw(vLine, 2, PrimitiveType::Lines);
	window.draw(hLine, 2, PrimitiveType::Lines);

	if (!isDivided)return;
	for (QuadTree<T>* children : this->subNodes)
		children->Draw(window);
}

//Rectangle based query
template<typename T>
void QuadTree<T>::Query(FloatRect boundary, list<T*>* boidList, BoidType boidType) {
	if (!this->boundary.intersects(boundary))									//If the boundary is not inside the area
		return;

	for (BaseBoid* b : this->boids) {
		if ((boidType == BoidType::eBaseBoid || b->boidType == boidType)		//If base boid was chosen or boid type same as search boid type
			&& inBounds(boundary, b->getPosition()))							//And its in the same boundary
			boidList->push_back(b);												//Add boids that are inside
	}

	if (!isDivided)																//If it hasnt been divided dont check children
		return;

	this->subNodes[0]->Query(boundary, boidList);
	this->subNodes[1]->Query(boundary, boidList);
	this->subNodes[2]->Query(boundary, boidList);
	this->subNodes[3]->Query(boundary, boidList);
}

//Radius based Query
template<typename T>
void QuadTree<T>::Query(Vector2f position, float visualRange, list<T*>* boidList, BoidType boidType) {
	if (!CircRectIntersects(boundary, position, visualRange))							//If the boundary is not inside the area
		return;

	for (BaseBoid* b : this->boids) {
		if ((boidType == BoidType::eBaseBoid || b->boidType == boidType)	//If base boid was chosen or boid type same as search boid type
			&& inRadius(position, visualRange, b->getPosition()))			//And its in the same Radius (not same boid)
			boidList->push_back(b);											//Add boids that are inside
	}

	if (!isDivided)															//If it hasnt been divided dont check children
		return;

	this->subNodes[0]->Query(position, visualRange, boidList);
	this->subNodes[1]->Query(position, visualRange, boidList);
	this->subNodes[2]->Query(position, visualRange, boidList);
	this->subNodes[3]->Query(position, visualRange, boidList);
}

template<typename T>
void QuadTree<T>::Clear() {
	boids.clear();
	if (isDivided) {
		for (QuadTree<T>* qt : subNodes) {
			qt->Clear();
			delete qt;
			qt = nullptr;
		}
	}
	isDivided = false;
	this->capacity = QUADCAPACITY;
}