// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "game.h"

GridSquare::GridSquare(std::string path, std::string _id, glm::vec3 _position, float _scale) : id(_id) {

	iGridSquare = Image(path, _position, _scale);

	rect.x = _position.x - ((_scale * iGridSquare.GetSize()->x) / 2);
	rect.y = _position.y - ((_scale * iGridSquare.GetSize()->y) / 2);
	rect.width = _scale * iGridSquare.GetSize()->x;
	rect.height = _scale * iGridSquare.GetSize()->y;
}

void GridSquare::Render() const {
	iGridSquare.Render();
}

std::string GridSquare::GetID() const {
	return id;
}

Rect::XYWH GridSquare::GetRect() const {
	return rect;
}

Grid::Grid() {

	float x = 20;
	float y = 580;

	char rows[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	char cols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	char baseRow = rows[0];
	char baseCol = cols[0];

	int br = 0;

	for (unsigned int z = 0; z < 100; z++) {

		if (z % 10 == 0) {

			y -= 40;
			x = 20;

			baseRow = rows[br];
			br++;
		}

		x += 40;
		baseCol = cols[z % 10];

		std::stringstream _id;
		_id << baseRow << baseCol;

		vGrid.push_back(GridSquare("Assets/Sprites/gridsquare.png", _id.str(), glm::vec3(x, y, 0)));
	}
}

void Grid::Update() {

	for (unsigned int x = 0; x < vGrid.size(); x++) {

		double mouseX = Mouse::GetMouseX();
		double mouseY = Mouse::GetMouseY();

		Rect::XYWH rect = vGrid[x].GetRect();

		if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
			(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
			(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

			if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
				//std::cout << vGrid[x].GetID() << std::endl;
				continue;
			}
		}
	}
}

void Grid::Render() const {

	for (unsigned int x = 0; x < vGrid.size(); x++) {
		vGrid[x].Render();
	}
}
