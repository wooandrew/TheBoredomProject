// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "game.h"

#pragma warning(disable: 26495)
GridSquare::GridSquare() : id("NULL") { }

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

Image* GridSquare::GetImage() {
	return &iGridSquare;
}

glm::vec3* GridSquare::GetPosition() {
	return iGridSquare.GetPosition();
}

bool operator==(const GridSquare& left, const GridSquare& right) {

	if (left.id == right.id) {
		return true;
	}

	return false;
}

Grid::Grid(float GridSize) {

	const char* pGridSpace = "Assets/gridspace.png";
	const char* pGridSquare = "Assets/gridsquare.png";

	if (GridSize == 54.5) {
		pGridSpace = "Assets/gridspacefull.png";
		pGridSquare = "Assets/gridsquarefull.png";
	}

	Image iGridSpace(pGridSpace, glm::vec3(GridSize * 6, Engine::SCREEN_HEIGHT - (GridSize * 6), 0), 1.0f);
	Rect::XYWH GSRect;
	GSRect.x = iGridSpace.GetPosition()->x - ((iGridSpace.GetScale()->x * iGridSpace.GetSize()->x) / 2);
	GSRect.y = iGridSpace.GetPosition()->y - ((iGridSpace.GetScale()->y * iGridSpace.GetSize()->y) / 2);
	GSRect.width = iGridSpace.GetScale()->x * iGridSpace.GetSize()->x;
	GSRect.height = iGridSpace.GetScale()->y * iGridSpace.GetSize()->y;

	GridSpace = std::make_pair(iGridSpace, GSRect);

	float x = GridSize / 2;
	float y = 600 - (GridSize / 2);

	char rows[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	char cols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	char baseRow = rows[0];
	char baseCol = cols[0];

	int br = 0;

	for (unsigned int z = 0; z < 100; z++) {

		if (z % 10 == 0) {

			y -= GridSize;
			x = GridSize / 2;

			baseRow = rows[br];
			br++;
		}

		x += GridSize;
		baseCol = cols[z % 10];

		std::ostringstream _id;
		_id << baseRow << baseCol;

		vGrid.push_back(GridSquare(pGridSquare, _id.str(), glm::vec3(x, y, 0)));
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
			}
		}
	}
}

void Grid::Render(bool debug) const {

	if (debug) {

		//GridSpace.first.Render();

		for (unsigned int x = 0; x < vGrid.size(); x++) {
			vGrid[x].Render();
		}
	}
}

void Grid::Reset() {
	IllegalSquares.clear();
}

void Grid::MakeIllegal(GridSquare square) {

	for (const GridSquare tGridSquare : IllegalSquares) {
		
		if (tGridSquare == square) {
			return;
		}
	}

	IllegalSquares.push_back(square);
}

void Grid::MakeLegal(GridSquare square) {
	IllegalSquares.remove(square);
}

bool Grid::IsLegal(GridSquare square) {

	for (const GridSquare tGridSquare : IllegalSquares) {

		if (tGridSquare == square) {
			return false;
		}
	}

	return true;
}

std::vector<GridSquare> Grid::GetGrid() const {
	return vGrid;
}

std::pair<Image, Rect::XYWH> Grid::GetGridSpace() const {
	return GridSpace;
}

std::list<GridSquare> Grid::GetIllegalSquares() const {
	return IllegalSquares;
};

GridSquare Grid::GetPressedSquare() const {

	for (unsigned int x = 0; x < vGrid.size(); x++) {

		double mouseX = Mouse::GetMouseX();
		double mouseY = Mouse::GetMouseY();

		Rect::XYWH rect = vGrid[x].GetRect();

		if ((mouseX < Engine::SCREEN_WIDTH) && (mouseX > 0) && (mouseY < Engine::SCREEN_HEIGHT) && (mouseY > 0) &&
			(mouseX > rect.x) && (static_cast<float>(mouseX) < rect.x + rect.width) &&
			(mouseY > rect.y) && (static_cast<float>(mouseY) < rect.y + rect.height)) {

			if (Mouse::ButtonIsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
				return vGrid[x];
			}
		}
	}
	return GridSquare();
}

void PrintIllegalSquares(Grid _grid) { // Debug Function

	for (const GridSquare tGridSquare : _grid.IllegalSquares) {
		std::cout << tGridSquare.GetID() << std::endl;
	}
	std::cout << "-----" << std::endl;
}

Pin::Pin(GridSquare gs, bool _hit) : GridSquareID(gs.GetID()) {

	if (_hit) {
		iPin = Image("Assets/goodattack.png", *gs.GetPosition(), 1.0f);
	}
	else {
		iPin = Image("Assets/badattack.png", *gs.GetPosition(), 1.0f);
	}
}

void Pin::Render() const {
	iPin.Render();
}

Attack::Attack() {
	goodhitnum = 0;
}

void Attack::Render() {

	for (const Pin pin : pins) {
		pin.Render();
	}
}

void Attack::Reset() {

	Attacked.clear();
	pins.clear();
	goodhitnum = 0;
}

void Attack::AttackSquare(GridSquare _gridsquare, bool goodhit) {
	
	for (const GridSquare gs : Attacked) {

		if (gs == _gridsquare) {
			return;
		}
	}

	Attacked.push_back(_gridsquare);
	pins.push_back(Pin(_gridsquare, goodhit));

	if (goodhit) {
		goodhitnum++;
	}
}

int Attack::GetGoodHitNum() const {
	return goodhitnum;
}

std::vector<GridSquare> Attack::GetAttacked() const {
	return Attacked;
}

std::pair<std::string, std::string> ParseRecvData(const char* ccRecvData) {

	std::vector<std::string> vaRecvData = Utilities::split(ccRecvData, ':');

	for (std::string datum : vaRecvData) {

		if (datum == "attack") {
			return std::make_pair(vaRecvData[0], vaRecvData[1]);
		}
	}

	return std::make_pair("NULLDATA", "NULLDATA");
}

void ParseRecvData(Player& player, const char* ccRecvData) {

	std::vector<std::string> vaRecvData = Utilities::split(ccRecvData, '&');

	for (std::string datum : vaRecvData) {

		if (datum == "not_ready") {
			player.Ready = false;
		}
		else if (datum == "ready") {
			player.Ready = true;
		}
		else {

			std::vector<std::string> csi = Utilities::split(datum, ':');

			if (csi[0] == "illegal_squares") {

				player.ViableSquareIDs.clear();

				for (unsigned int x = 1; x < csi.size(); x++) {
					player.ViableSquareIDs.push_back(csi[x]);
				}
			}
			else if (csi[0] == "placed_ids") {

				player.PlacedIDs.clear();

				for (unsigned int x = 1; x < csi.size(); x++) {
					player.PlacedIDs.push_back(csi[x]);
				}
			}
			else if (csi[0] == "csg_rotations") { // Unused

				player.ShipRotations.clear();

				for (unsigned int x = 1; x < csi.size(); x++) {
					player.ShipRotations.push_back(csi[x]);
				}
			}
		}
	}
}

GridSquare IDtoGR(Grid& _grid, std::string _id) {

	for (const GridSquare gs : _grid.GetGrid()) {

		if (gs.GetID() == _id) {
			return gs;
		}
	}

	return GridSquare();
}
