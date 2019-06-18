// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "ship.h"

Ship::Ship(std::string path, ShipType _type, glm::vec3 _position, float _scale) : type(_type), defaultPosition(_position) {

	iShip = Image(path, _position, _scale);
	
	selected = false;
	placed = false;

	rect.x = _position.x - ((_scale * iShip.GetSize()->x) / 2);
	rect.y = _position.y - ((_scale * iShip.GetSize()->y) / 2);
	rect.width = _scale * iShip.GetSize()->x;
	rect.height = _scale * iShip.GetSize()->y;
}

Ship::Ship(Image& _iShip, ShipType _type) : type(_type), defaultPosition(*_iShip.GetPosition()) {

	iShip = _iShip;
	
	selected = false;
	placed = false;

	rect.x = iShip.GetPosition()->x - ((iShip.GetScale()->x * iShip.GetSize()->x) / 2);
	rect.y = iShip.GetPosition()->y - ((iShip.GetScale()->y * iShip.GetSize()->y) / 2);
	rect.width = iShip.GetScale()->x * iShip.GetSize()->x;
	rect.height = iShip.GetScale()->y * iShip.GetSize()->y;
}

void Ship::Update(Grid& _grid, bool setup) {

	if (setup) {

		double mouseX = Mouse::GetMouseX();
		double mouseY = Mouse::GetMouseY();

		if (selected) {

			if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {

				selected = false;
				placed = false;

				iShip.SetPosition(defaultPosition);
				iShip.RotateTo(0);

				UpdateRect();

				return;
			}
			else if (Keyboard::KeyDown(GLFW_KEY_R)) {

				static int rotation = 90;

				if (rotation == 90) {
					iShip.RotateTo(static_cast<float>(rotation));
					rotation = 0;
				}
				else {
					iShip.RotateTo(static_cast<float>(rotation));
					rotation = 90;
				}
			}
			else if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {

				for (unsigned int x = 0; x < _grid.GetGrid().size(); x++) {

					Rect::XYWH r_gridSquare = _grid.GetGrid()[x].GetRect();

					if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
						(mouseX > r_gridSquare.x) && (static_cast<float>(mouseX) < r_gridSquare.x + r_gridSquare.width) &&
						(mouseY > r_gridSquare.y) && (static_cast<float>(mouseY) < r_gridSquare.y + r_gridSquare.height)) {

						if (static_cast<int>(*iShip.GetRotation()) == 90) {

							if (type == ShipType::Cruiser || type == ShipType::Supply) {
								iShip.SetPosition(glm::vec3(_grid.GetGrid()[x].GetPosition()->x, _grid.GetGrid()[x].GetPosition()->y - 20, 0));
							}
							else {
								iShip.SetPosition(*_grid.GetGrid()[x].GetPosition());
							}
						}
						else {

							if (type == ShipType::Cruiser || type == ShipType::Supply) {
								iShip.SetPosition(glm::vec3(_grid.GetGrid()[x].GetPosition()->x - 20, _grid.GetGrid()[x].GetPosition()->y, 0));
							}
							else {
								iShip.SetPosition(*_grid.GetGrid()[x].GetPosition());
							}
						}
						
						UpdateRect();

						for (const GridSquare tGridSquare : _grid.GetGrid()) {

							if (rect.CheckCollisionAABB(tGridSquare.GetRect())) {
								continue;
							}
						}
						
						selected = false;
						placed = true;

						return;
					}
				}
			}
			else {
				iShip.SetPosition(glm::vec3(Mouse::GetMouseX(), Mouse::GetMouseY(), 0));
			}

			UpdateRect();
		}
		else {

			if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
				(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
				(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

				if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
					selected = true;
				}
			}
		}
	}
}

void Ship::Render() const {
	iShip.Render();
}

void Ship::UpdateRect() {

	if (static_cast<int>(*iShip.GetRotation()) == 0) {

		rect.x = iShip.GetPosition()->x - ((iShip.GetScale()->x * iShip.GetSize()->x) / 2);
		rect.y = iShip.GetPosition()->y - ((iShip.GetScale()->y * iShip.GetSize()->y) / 2);
		rect.width = iShip.GetScale()->x * iShip.GetSize()->x;
		rect.height = iShip.GetScale()->y * iShip.GetSize()->y;
	}
	else if (static_cast<int>(*iShip.GetRotation()) == 90) {

		rect.x = iShip.GetPosition()->x - ((iShip.GetScale()->y * iShip.GetSize()->y) / 2);
		rect.y = iShip.GetPosition()->y - ((iShip.GetScale()->x * iShip.GetSize()->x) / 2);
		rect.width = iShip.GetScale()->y * iShip.GetSize()->y;
		rect.height = iShip.GetScale()->x * iShip.GetSize()->x;
	}
}

bool Ship::GetPlaced() const {
	return placed;
}
