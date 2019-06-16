// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "ship.h"

Ship::Ship(std::string path, glm::vec3 _position, float _scale) : defaultPosition(_position) {

	iShip = Image(path, _position, _scale);
	selected = false;

	rect.x = _position.x - ((_scale * iShip.GetSize()->x) / 2);
	rect.y = _position.y - ((_scale * iShip.GetSize()->y) / 2);
	rect.width = _scale * iShip.GetSize()->x;
	rect.height = _scale * iShip.GetSize()->y;
}

Ship::Ship(Image& _iShip) : defaultPosition(*_iShip.GetPosition()) {

	iShip = _iShip;
	selected = false;

	rect.x = iShip.GetPosition()->x - ((iShip.GetScale()->x * iShip.GetSize()->x) / 2);
	rect.y = iShip.GetPosition()->y - ((iShip.GetScale()->y * iShip.GetSize()->y) / 2);
	rect.width = iShip.GetScale()->x * iShip.GetSize()->x;
	rect.height = iShip.GetScale()->y * iShip.GetSize()->y;
}

void Ship::Update(bool setup) {

	if (setup) {

		double mouseX = Mouse::GetMouseX();
		double mouseY = Mouse::GetMouseY();

		if (selected) {

			if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {

				selected = false;

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
					
				UpdateRect();
			}

			iShip.SetPosition(glm::vec3(Mouse::GetMouseX(), Mouse::GetMouseY(), 0));
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

	rect.x = iShip.GetPosition()->x - ((iShip.GetScale()->x * iShip.GetSize()->x) / 2);
	rect.y = iShip.GetPosition()->y - ((iShip.GetScale()->y * iShip.GetSize()->y) / 2);
	rect.width = iShip.GetScale()->x * iShip.GetSize()->x;
	rect.height = iShip.GetScale()->y * iShip.GetSize()->y;
}
