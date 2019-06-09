// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "button.h"

Button::Button(std::string path, glm::vec3 _position, float scale, Misc::GameState _retVal, bool _HideAwayButton) {

	buttonimage = Image(path, _position, scale);

	buttonPressable = true;
	HideAwayButton = _HideAwayButton;

	retVal = _retVal;

	rect.x = _position.x - ((scale * buttonimage.GetSize()->x) / 2);
	rect.y = _position.y - ((scale * buttonimage.GetSize()->y) / 2);
	rect.width = scale * buttonimage.GetSize()->x;
	rect.height = scale * buttonimage.GetSize()->y;
}

Button::Button(Image& _buttonimage, Misc::GameState _retVal, bool _HideAwayButton) {

	buttonimage = _buttonimage;
	
	buttonPressable = true;
	HideAwayButton = _HideAwayButton;

	retVal = _retVal;

	rect.x = buttonimage.GetPosition()->x - ((buttonimage.GetScale()->x * buttonimage.GetSize()->x) / 2);
	rect.y = buttonimage.GetPosition()->y - ((buttonimage.GetScale()->y * buttonimage.GetSize()->y) / 2);
	rect.width = buttonimage.GetScale()->x * buttonimage.GetSize()->x;
	rect.height = buttonimage.GetScale()->y * buttonimage.GetSize()->y;
}

void Button::HideAway(int xmax, int xmin, bool use) {

	if (use) {

		double mouseX = Mouse::GetMouseX();
		double mouseY = Mouse::GetMouseY();

		if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
			(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
			(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

			if (buttonimage.GetPosition()->x > xmin) {

				double moveX = buttonimage.GetPosition()->x - (1000 * Misc::GetDeltaTime());
				buttonimage.SetPosition(glm::vec3(moveX, buttonimage.GetPosition()->y, 0));
				UpdateRect();
			}
			else if (buttonimage.GetPosition()->x < xmin) {
				buttonimage.SetPosition(glm::vec3(xmin, buttonimage.GetPosition()->y, 0));
			}

		}
		else {

			if (buttonimage.GetPosition()->x < xmax) {

				double moveX = buttonimage.GetPosition()->x + (1000 * Misc::GetDeltaTime());
				buttonimage.SetPosition(glm::vec3(moveX, buttonimage.GetPosition()->y, 0));
				UpdateRect();
			}
			else if (buttonimage.GetPosition()->x > xmax) {
				buttonimage.SetPosition(glm::vec3(xmax, buttonimage.GetPosition()->y, 0));
			}
		}
	}
}

Misc::GameState Button::Update(Misc::GameState currentstate, int xmax, int xmin) {

	double mouseX = Mouse::GetMouseX();
	double mouseY = Mouse::GetMouseY();

	if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
		(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
		(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

		if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			buttonPressable = false;
			return retVal;
		}
		else if (!Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			buttonPressable = true;
		}
	}
	HideAway(xmax, xmin, HideAwayButton);

	return currentstate;
}

void Button::UpdateRect() {

	rect.x = buttonimage.GetPosition()->x - ((buttonimage.GetScale()->x * buttonimage.GetSize()->x) / 2);
	rect.y = buttonimage.GetPosition()->y - ((buttonimage.GetScale()->y * buttonimage.GetSize()->y) / 2);
	rect.width = buttonimage.GetScale()->x * buttonimage.GetSize()->x;
	rect.height = buttonimage.GetScale()->y * buttonimage.GetSize()->y;
}

Image Button::GetImage() const { return buttonimage; }

std::ostream& operator<<(std::ostream& os, Rect right) {
	os << right.x << " : " << right.y << " : " << right.width << " : " << right.height;
	return os;
}
