#include "World.h"

World::World(){
	WorldV.setCenter(WORLDSIZE / 2, WORLDSIZE / 2);						//What the view is centered in
	WorldV.setSize(WORLDSIZE / 2, WORLDSIZE / 2);						//What the view can see	(the screen size/2)
	WorldV.setViewport(FloatRect(MWIDTHPer, 0, GWIDTHPer, 1.f));		//Top,left,width,height of the viewport
	
	GenerateWorld();
}

void World::GenerateWorld(){
	fillRandom();
	int neighbors;
	for (int i = 0; i < 15; i++) {
		for (int y = 0; y < WORLDSIZE; y++) {
			for (int x = 0; x < WORLDSIZE; x++) {
				neighbors = getNeighbors(x, y);
				grid[y][x] = (neighbors == 4 && lastGrid[y][x]) || neighbors >= 5;
			}
		}
		copyWorld();
	}

	for (int y = WORLDSIZE * 0.33; y < WORLDSIZE * 0.66; y++) {
		for (int x = WORLDSIZE * 0.33; x < WORLDSIZE * 0.66; x++) {
			grid[y][x] = 0;
		}
	}
}

void World::drawWorld(RenderWindow& window){
	//RectangleShape rect;
	//window.setView(WorldV);
	////rect.setRadius((GHEIGHT / (WORLDSIZE * 1.2)) * 2);
	////rect.setRadius(2);
	//rect.setSize({ 2,2 });
	//rect.setFillColor(Color::Black);
	//RectangleShape wholeRect;							//FILLS WHOLE SCREEN,CAN DELETE
	//wholeRect.setSize({ GWIDTH,GHEIGHT });
	//wholeRect.setFillColor(Color::White);
	//window.draw(wholeRect);
	//for (int y = 0; y < WORLDSIZE; y++) {
	//	for (int x = 0; x < WORLDSIZE; x++) {
	//		if (grid[y][x]) {
	//			//rect.setPosition(Vector2f(x * (GWIDTH / WORLDSIZE), y * (HEIGHT / WORLDSIZE)));
	//			rect.setPosition(x, y);
	//			window.draw(rect);
	//		}
	//	}
	//}
}

void World::Zoom(float zAmount)
{
}

void World::changeSize(Vector2f size) {
	WorldV.setSize(WorldV.getSize()+size);
	std::cout << "World: " << WorldV.getSize().x << " " << WorldV.getSize().y << std::endl;
}

void World::fillRandom(){
	srand(time(NULL));
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			grid[y][x] = rand() % 101 < 40;
			lastGrid[y][x] = grid[y][x];
		}
	}
}

int World::getNeighbors(int x, int y){
	bool hasBelow = y < WORLDSIZE - 4;
	bool hasAbove = y > 4;
	bool hasLeft = x > 4;
	bool hasRight = x < WORLDSIZE - 4;

	return (!hasAbove || lastGrid[y - 1][x]) +
		(!hasAbove || !hasLeft || lastGrid[y - 1][x - 1]) +
		(!hasAbove || !hasRight || lastGrid[y - 1][x + 1]) +
		(!hasLeft || lastGrid[y][x - 1]) +
		(!hasRight || lastGrid[y][x + 1]) +
		(!hasBelow || lastGrid[y + 1][x]) +
		(!hasBelow || !hasLeft || lastGrid[y + 1][x - 1]) +
		(!hasBelow || !hasRight || lastGrid[y + 1][x + 1]);
}

void World::copyWorld(){
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			lastGrid[y][x] = grid[y][x];
		}
	}
}