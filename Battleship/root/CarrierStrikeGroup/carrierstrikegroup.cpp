// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "carrierstrikegroup.h"

Ships::Ships() {
	ready = false;
}

Ships::Ships(std::vector<glm::vec3> defPos, bool full) {

	if (!full) {

		AircraftCarrier = Ship("Assets/Sprites/carrier.png", ShipType::AircraftCarrier, defPos[0]);
		Cruiser = Ship("Assets/Sprites/cruiser.png", ShipType::Cruiser, defPos[1]);
		Destroyer1 = Ship("Assets/Sprites/destroyer.png", ShipType::Destroyer, defPos[2]);
		Destroyer2 = Ship("Assets/Sprites/destroyer.png", ShipType::Destroyer, defPos[3]);
		Supply = Ship("Assets/Sprites/supply.png", ShipType::Supply, defPos[4]);
		Submarine = Ship("Assets/Sprites/submarine.png", ShipType::Submarine, defPos[5]);
	}
	else {

		AircraftCarrier = Ship("Assets/Sprites/carrierfull.png", ShipType::AircraftCarrier, defPos[0]);
		Cruiser = Ship("Assets/Sprites/cruiserfull.png", ShipType::Cruiser, defPos[1]);
		Destroyer1 = Ship("Assets/Sprites/destroyerfull.png", ShipType::Destroyer, defPos[2]);
		Destroyer2 = Ship("Assets/Sprites/destroyerfull.png", ShipType::Destroyer, defPos[3]);
		Supply = Ship("Assets/Sprites/supplyfull.png", ShipType::Supply, defPos[4]);
		Submarine = Ship("Assets/Sprites/submarinefull.png", ShipType::Submarine, defPos[5]);
	}

	ready = false;
}

void Ships::Update(Grid& _grid, bool setup) {

	AircraftCarrier.Update(_grid, setup);
	Cruiser.Update(_grid, setup);
	Destroyer1.Update(_grid, setup);
	Destroyer2.Update(_grid, setup);
	Supply.Update(_grid, setup);
	Submarine.Update(_grid, setup);

	ready = (AircraftCarrier.GetPlaced() && Cruiser.GetPlaced() && Destroyer1.GetPlaced() 
			&& Destroyer2.GetPlaced() && Supply.GetPlaced() && Submarine.GetPlaced());
}

void Ships::Render() const {
	
	AircraftCarrier.Render();
	Cruiser.Render();
	Destroyer1.Render();
	Destroyer2.Render();
	Supply.Render();
	Submarine.Render();
}

void Ships::Reset() {

	AircraftCarrier.Reset();
	Cruiser.Reset();
	Destroyer1.Reset();
	Destroyer2.Reset();
	Supply.Reset();
	Submarine.Reset();
}

void Ships::Assemble(std::vector<glm::vec3> defPos, std::vector<std::string> _vRotations) {

	AircraftCarrier.GetImage()->SetPosition(defPos[0]);		AircraftCarrier.GetImage()->RotateTo(std::stof(_vRotations[0]));		AircraftCarrier.UpdateRect();
	Cruiser.GetImage()->SetPosition(defPos[1]);				Cruiser.GetImage()->RotateTo(std::stof(_vRotations[1]));				Cruiser.UpdateRect();
	Destroyer1.GetImage()->SetPosition(defPos[2]);			Destroyer1.GetImage()->RotateTo(std::stof(_vRotations[2]));				Destroyer1.UpdateRect();
	Destroyer2.GetImage()->SetPosition(defPos[3]);			Destroyer2.GetImage()->RotateTo(std::stof(_vRotations[3]));				Destroyer2.UpdateRect();
	Supply.GetImage()->SetPosition(defPos[4]);				Supply.GetImage()->RotateTo(std::stof(_vRotations[4]));					Supply.UpdateRect();
	Submarine.GetImage()->SetPosition(defPos[5]);			Submarine.GetImage()->RotateTo(std::stof(_vRotations[5]));				Submarine.UpdateRect();
}

CarrierStrikeGroup::CarrierStrikeGroup() {}

CarrierStrikeGroup::CarrierStrikeGroup(std::vector<glm::vec3> defPos, bool full) {
	StrikeGroup = Ships(defPos, full);
}

void CarrierStrikeGroup::Update(Grid& _grid, bool setup) {
	StrikeGroup.Update(_grid, setup);
}

void CarrierStrikeGroup::Render() const {
	StrikeGroup.Render();
}

void CarrierStrikeGroup::Reset() {
	StrikeGroup.Reset();
}

void CarrierStrikeGroup::Assemble(std::vector<glm::vec3> defPos) {
	StrikeGroup.Assemble(defPos);
}

void CarrierStrikeGroup::Assemble(Grid& _grid, std::string _placedids, std::string _rotations) {

	std::vector<std::string> vPlacedIDs = Utilities::split(_placedids, ':');
	std::vector<std::string> vRotations = Utilities::split(_rotations, ':');

	std::vector<glm::vec3> defPos;

	for (unsigned int x = 0; x < vPlacedIDs.size(); x++) {

		for (GridSquare tGridSquare : _grid.GetGrid()) {

			if (tGridSquare.GetID() == vPlacedIDs[x]) {

				if (x == 1) {

					if (static_cast<int>(std::stof(vRotations[1])) == 90) {
						defPos.push_back(glm::vec3(tGridSquare.GetPosition()->x, tGridSquare.GetPosition()->y - 27, 0));
					}
					else {
						defPos.push_back(glm::vec3(tGridSquare.GetPosition()->x - 27, tGridSquare.GetPosition()->y, 0));
					}
				}
				else if (x == 4) {

					if (static_cast<int>(std::stof(vRotations[4])) == 90) {
						defPos.push_back(glm::vec3(tGridSquare.GetPosition()->x, tGridSquare.GetPosition()->y - 27, 0));
					}
					else {
						defPos.push_back(glm::vec3(tGridSquare.GetPosition()->x - 27, tGridSquare.GetPosition()->y, 0));
					}
				}
				else {
					defPos.push_back(*tGridSquare.GetPosition());
				}

				break;
			}
		}
	}

	StrikeGroup.Assemble(defPos, vRotations);
}

bool CarrierStrikeGroup::GetReady() const { // Returns [true] if all Ships have been placed.
	return StrikeGroup.ready;
}

std::string CarrierStrikeGroup::GetPlacedIDs() const {
	return StrikeGroup.AircraftCarrier.GetPlacedID() + ":" + StrikeGroup.Cruiser.GetPlacedID() + ":" + StrikeGroup.Destroyer1.GetPlacedID() + ":" + 
		   StrikeGroup.Destroyer2.GetPlacedID() + ":" + StrikeGroup.Supply.GetPlacedID() + ":" + StrikeGroup.Submarine.GetPlacedID();
}

std::string CarrierStrikeGroup::GetRotations() {

	return std::to_string(static_cast<int>(*StrikeGroup.AircraftCarrier.GetImage()->GetRotation())) + ":" + std::to_string(static_cast<int>(*StrikeGroup.Cruiser.GetImage()->GetRotation())) + ":" +
		   std::to_string(static_cast<int>(*StrikeGroup.Destroyer1.GetImage()->GetRotation())) + ":" + std::to_string(static_cast<int>(*StrikeGroup.Destroyer2.GetImage()->GetRotation())) + ":" +
		   std::to_string(static_cast<int>(*StrikeGroup.Supply.GetImage()->GetRotation())) + ":" + std::to_string(static_cast<int>(*StrikeGroup.Submarine.GetImage()->GetRotation()));
}
