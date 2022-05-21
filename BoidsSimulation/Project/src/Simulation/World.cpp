#include "World.h"

World::World() {
	WorldV.setCenter(WORLDSIZE / 2, WORLDSIZE / 2);						//What the view is centered in
	WorldV.setSize(WORLDSIZE, WORLDSIZE);						//What the view can see	(the screen size/2)
	WorldV.setViewport(sf::FloatRect(MWIDTHPer, 0, GWIDTHPer, 1.f));		//Top,left,width,height of the viewport

	GenerateWorld();
	GenerateTexture();
}

void World::drawWorld(sf::RenderWindow& window) {
	window.setView(WorldV);
	window.draw(gridSprite);
}

void World::GenerateWorld() {
	fillRandom();
	int neighbors;
	for (int step = 0; step < numberOfSteps; step++) {
		for (int y = 0; y < WORLDSIZE; y++) {
			for (int x = 0; x < WORLDSIZE; x++) {
				neighbors = getNeighbors(x, y);
				grid[y][x] = (neighbors == 4 && lastGrid[y][x]) || neighbors >= 5;
			}
		}
		copyWorld();
	}
}
//sf::RectangleShape rect;
//rect.setSize({ 2,2 });
//rect.setFillColor(sf::Color(50, 50, 50));
//rect.setPosition(sf::Vector2f(x * (GWIDTH / WORLDSIZE), y * (HEIGHT / WORLDSIZE)));
//gridTexture.draw(rect);
void World::GenerateTexture() {
	gridTexture.create(WORLDSIZE, WORLDSIZE);
	gridTexture.clear(sf::Color::Black);
	sf::CircleShape circ;
	circ.setRadius((GHEIGHT / (REALWORLDSIZE * 1.2)) * 2);
	circ.setFillColor(sf::Color(50, 50, 50));
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			if (grid[y][x]) {
				circ.setPosition(x, y);
				gridTexture.draw(circ);
			}
		}
	}
	gridSprite.setTexture(gridTexture.getTexture());
}

void World::Zoom(float zAmount) {

}

void World::changeSize(sf::Vector2f size) {
	WorldV.setSize(WorldV.getSize() + size);
	std::cout << "World: " << WorldV.getSize().x << " " << WorldV.getSize().y << std::endl;
}

void World::ReGenerateWorld(){
	GenerateWorld();
	GenerateTexture();
}

void World::setView(sf::Vector2f pos) {
	WorldV.setCenter((pos.x / GWIDTH) * WORLDSIZE, (pos.y / GHEIGHT) * WORLDSIZE);
	WorldV.setSize(WORLDSIZE / 3, WORLDSIZE / 3);
}

void World::setDefaultView() {
	WorldV.setCenter(WORLDSIZE / 2, WORLDSIZE / 2);
	WorldV.setSize(WORLDSIZE, WORLDSIZE);
}

void World::fillRandom() {
	srand(time(NULL));
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			grid[y][x] = rand() % 101 < 40;
			lastGrid[y][x] = grid[y][x];
		}
	}
}

int World::getNeighbors(int x, int y) {
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

void World::copyWorld() {
	for (int y = 0; y < WORLDSIZE; y++) {
		for (int x = 0; x < WORLDSIZE; x++) {
			lastGrid[y][x] = grid[y][x];
		}
	}
}
