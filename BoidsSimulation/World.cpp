#include "World.h"

World::World(){
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
}

void World::drawWorld(RenderWindow& window){
	CircleShape rect;
	//rect.setRadius((GHEIGHT / (WORLDSIZE * 1.2)) * 2);
	rect.setRadius(1);
	rect.setFillColor(Color::Black);
	RectangleShape wholeRect;							//FILLS WHOLE SCREEN,CAN DELETE
	wholeRect.setSize({ GWIDTH,GHEIGHT });
	wholeRect.setFillColor(Color::White);
	window.draw(wholeRect);
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			if (grid[y][x]) {
				//rect.setPosition(Vector2f(x * (GWIDTH / WORLDSIZE), y * (HEIGHT / WORLDSIZE)));
				rect.setPosition(x, y);
				window.draw(rect);
			}
		}
	}
}

void World::fillRandom(){
	srand(time(NULL));
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			grid[y][x] = rand() % 101 < 45;
			lastGrid[y][x] = grid[y][x];
		}
	}
}

int World::getNeighbors(int x, int y){
	bool hasBelow = y < WORLDSIZE - 2;
	bool hasAbove = y > 2;
	bool hasLeft = x > 2;
	bool hasRight = x < WORLDSIZE - 2;

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
