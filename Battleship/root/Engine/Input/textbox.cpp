// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "textbox.h"

Textbox::Textbox(std::string path, glm::vec3 _position, float scale, bool _update) {

	tbImage = Image(path, _position, scale);

	update = _update;

	rect.x = _position.x - ((scale * tbImage.GetSize()->x) / 2);
	rect.y = _position.y - ((scale * tbImage.GetSize()->y) / 2);
	rect.width = scale * tbImage.GetSize()->x;
	rect.height = scale * tbImage.GetSize()->y;
}

Textbox::Textbox(Image& _tbImage, bool _update) {

	tbImage = _tbImage;

	update = _update;

	rect.x = tbImage.GetPosition()->x - ((tbImage.GetScale()->x * tbImage.GetSize()->x) / 2);
	rect.y = tbImage.GetPosition()->y - ((tbImage.GetScale()->y * tbImage.GetSize()->y) / 2);
	rect.width = tbImage.GetScale()->x * tbImage.GetSize()->x;
	rect.height = tbImage.GetScale()->y * tbImage.GetSize()->y;
}

void Textbox::Update() {

	double mouseX = Mouse::GetMouseX();
	double mouseY = Mouse::GetMouseY();

	if (!update && (mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
		(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
		(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

		if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			update = true;
			Keyboard::ResetKeysPressed();
		}
	}

	if (update) {
		
		std::vector<int> _KeyPress = Keyboard::GetKeysPressed();

		if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
			(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
			(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

			if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_RIGHT)) {

				update = false;
				Keyboard::ResetKeysPressed();

				return;
			}
		}
		else {

			if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {

				update = false;
				Keyboard::ResetKeysPressed();

				return;
			}
		}

		for (int key : _KeyPress) {
			
			if (key == GLFW_KEY_BACKSPACE) {

				if (keyToChar.size() > 0) {
					keyToChar.pop_back();
				}
			}
			else {
				keyToChar.push_back(key);
			}
		}

		tbText = "";
		if(keyToChar.size() > 0){

			for (char letter : keyToChar) {
				tbText += letter;
			}
		}

		Keyboard::ResetKeysPressed();
	}
}

void Textbox::Render(Text& font, int size, glm::vec3 color) {
	tbImage.Render();
	font.RenderText(tbText, size, glm::vec3(rect.x, rect.y + 5, 0), color);
}

std::string Textbox::GetText() const {
	return tbText;
}

void Textbox::StopUpdate() {
	update = false;
}
