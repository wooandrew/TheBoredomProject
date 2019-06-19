// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "ship.h"

Ship::Ship() {}

Ship::Ship(std::string path, ShipType _type, glm::vec3 _position, float _scale) {

	iShip = Image(path, _position, _scale);
	
	selected = false;
	placed = false;

	rect.x = _position.x - ((_scale * iShip.GetSize()->x) / 2);
	rect.y = _position.y - ((_scale * iShip.GetSize()->y) / 2);
	rect.width = _scale * iShip.GetSize()->x;
	rect.height = _scale * iShip.GetSize()->y;

	type = _type;
	defaultPosition = _position;
}

Ship::Ship(Image& _iShip, ShipType _type) {

	iShip = _iShip;
	
	selected = false;
	placed = false;

	rect.x = iShip.GetPosition()->x - ((iShip.GetScale()->x * iShip.GetSize()->x) / 2);
	rect.y = iShip.GetPosition()->y - ((iShip.GetScale()->y * iShip.GetSize()->y) / 2);
	rect.width = iShip.GetScale()->x * iShip.GetSize()->x;
	rect.height = iShip.GetScale()->y * iShip.GetSize()->y;

	type = _type;
	defaultPosition = *_iShip.GetPosition();
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

					const Rect::XYWH r_GridSquare = _grid.GetGrid()[x].GetRect();
					const Rect::XYWH r_GridSpace = _grid.GetGridSpace().second;

					if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
						(mouseX > r_GridSquare.x) && (static_cast<float>(mouseX) < r_GridSquare.x + r_GridSquare.width) &&
						(mouseY > r_GridSquare.y) && (static_cast<float>(mouseY) < r_GridSquare.y + r_GridSquare.height)) {

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
						
						PlacedId = _grid.GetGrid()[x].GetID();
						
						UpdateRect();

						if ((rect.x <= r_GridSpace.x) || (rect.x + rect.width >= r_GridSpace.x + r_GridSpace.width) ||
							(rect.y <= r_GridSpace.y) || (rect.y + rect.height >= r_GridSpace.y + r_GridSpace.height)) {
							iShip.SetPosition(glm::vec3(Mouse::GetMouseX(), Mouse::GetMouseY(), 0));
							break;
						}

						std::vector<GridSquare> tempGS;

						for (const GridSquare tGridSquare : _grid.GetGrid()) {

							if (rect.CheckCollisionAABB(tGridSquare.GetRect())) {

								if (_grid.IsLegal(tGridSquare)) {
									tempGS.push_back(tGridSquare);
								}
								else {

									iShip.SetPosition(glm::vec3(Mouse::GetMouseX(), Mouse::GetMouseY(), 0));

									selected = true;
									placed = false;

									goto ExitGridLoop;
								}
							}
						}

						if (type != ShipType::Submarine) {
							
							for (const GridSquare tGridSquare : tempGS) {
								_grid.MakeIllegal(tGridSquare);
							}
						}
						else {
							_grid.MakeIllegal(tempGS[1]);
						}
						
						selected = false;
						placed = true;

					ExitGridLoop:

						break;
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
					placed = false;

					for (const GridSquare tGridSquare : _grid.GetGrid()) {

						if (rect.CheckCollisionAABB(tGridSquare.GetRect())) {
							_grid.MakeLegal(tGridSquare);
						}
					}
				}
			}
		}
	}

	
}

void Ship::Render() const {
	iShip.Render();
}

void Ship::Reset() {

	iShip.SetPosition(defaultPosition);
	iShip.RotateTo(0);

	UpdateRect();

	selected = false;
	placed = false;
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

Image* Ship::GetImage() {
	return &iShip;
}

bool Ship::GetPlaced() const {
	return placed;
}

std::string Ship::GetPlacedID() const {
	return PlacedId;
}
