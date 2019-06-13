// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE_INPUT_BUTTON
#define ENGINE_INPUT_BUTTON

#include "../../lib.h"

#include "../engine.h"
#include "../Math/math.h"
#include "../../Graphics/sprite.h"

#include "mouse.h"

template<typename RETURN>
class Button {

public:

	Button(std::string path, glm::vec3 _position, float scale, RETURN _retVal, bool _HideAwayButton = false) {

		buttonimage = Image(path, _position, scale);

		buttonPressable = true;
		HideAwayButton = _HideAwayButton;

		retVal = _retVal;

		rect.x = _position.x - ((scale * buttonimage.GetSize()->x) / 2);
		rect.y = _position.y - ((scale * buttonimage.GetSize()->y) / 2);
		rect.width = scale * buttonimage.GetSize()->x;
		rect.height = scale * buttonimage.GetSize()->y;
	}

	Button(Image& _buttonimage, RETURN _retVal, bool _HideAwayButton = false) {

		buttonimage = _buttonimage;

		buttonPressable = true;
		HideAwayButton = _HideAwayButton;

		retVal = _retVal;

		rect.x = buttonimage.GetPosition()->x - ((buttonimage.GetScale()->x * buttonimage.GetSize()->x) / 2);
		rect.y = buttonimage.GetPosition()->y - ((buttonimage.GetScale()->y * buttonimage.GetSize()->y) / 2);
		rect.width = buttonimage.GetScale()->x * buttonimage.GetSize()->x;
		rect.height = buttonimage.GetScale()->y * buttonimage.GetSize()->y;
	}

	RETURN Update(RETURN _return, int xmax = 0, int xmin = 0) {

		double mouseX = Mouse::GetMouseX();
		double mouseY = Mouse::GetMouseY();

		if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
			(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
			(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

			if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
				buttonPressable = false;
				return retVal;
			}
			else {
				buttonPressable = true;
			}
		}
		HideAway(xmax, xmin, HideAwayButton);

		return _return;
	}

	void Render() const {
		buttonimage.Render();
	}

	void HideAway(int xmax, int xmin, bool use) {

		if (use) {

			double mouseX = Mouse::GetMouseX();
			double mouseY = Mouse::GetMouseY();

			if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
				(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
				(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

				if (buttonimage.GetPosition()->x > xmin) {

					double moveX = buttonimage.GetPosition()->x - (1000 * Utilities::GetDeltaTime());
					buttonimage.SetPosition(glm::vec3(moveX, buttonimage.GetPosition()->y, 0));
					UpdateRect();
				}
				else if (buttonimage.GetPosition()->x < xmin) {
					buttonimage.SetPosition(glm::vec3(xmin, buttonimage.GetPosition()->y, 0));
					UpdateRect();
				}

			}
			else {

				if (buttonimage.GetPosition()->x < xmax) {

					double moveX = buttonimage.GetPosition()->x + (1000 * Utilities::GetDeltaTime());
					buttonimage.SetPosition(glm::vec3(moveX, buttonimage.GetPosition()->y, 0));
					UpdateRect();
				}
				else if (buttonimage.GetPosition()->x > xmax) {
					buttonimage.SetPosition(glm::vec3(xmax, buttonimage.GetPosition()->y, 0));
					UpdateRect();
				}
			}
		}
	}

	void UpdateRect() {

		rect.x = buttonimage.GetPosition()->x - ((buttonimage.GetScale()->x * buttonimage.GetSize()->x) / 2);
		rect.y = buttonimage.GetPosition()->y - ((buttonimage.GetScale()->y * buttonimage.GetSize()->y) / 2);
		rect.width = buttonimage.GetScale()->x * buttonimage.GetSize()->x;
		rect.height = buttonimage.GetScale()->y * buttonimage.GetSize()->y;
	}

	Image GetImage() const {
		return buttonimage;
	}

	bool GetButtonPressed() const {
		return !buttonPressable;
	}

private:

	bool buttonPressable;
	bool HideAwayButton;

	RETURN retVal;

	Image buttonimage;
	Rect::XYWH rect;
};

#endif // !ENGINE_INPUT_BUTTON

