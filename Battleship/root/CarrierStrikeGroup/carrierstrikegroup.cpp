// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "carrierstrikegroup.h"

Ships::Ships(std::vector<glm::vec3> defPos) : AircraftCarrier("Assets/Sprites/carrier.png", ShipType::AircraftCarrier, defPos[0]), 
											  Cruiser("Assets/Sprites/cruiser.png", ShipType::Cruiser, defPos[1]),
											  Destroyer1("Assets/Sprites/destroyer.png", ShipType::Destroyer, defPos[2]), 
											  Destroyer2("Assets/Sprites/destroyer.png", ShipType::Destroyer, defPos[3]),
											  Supply("Assets/Sprites/supply.png", ShipType::Supply, defPos[4]),
											  Submarine("Assets/Sprites/submarine.png", ShipType::Submarine, defPos[5]) {

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

CarrierStrikeGroup::CarrierStrikeGroup(std::vector<glm::vec3> defPos) : StrikeGroup(defPos) {
	
	ready = false;
}

void CarrierStrikeGroup::Update(Grid& _grid, bool setup) {
	StrikeGroup.Update(_grid, setup);
}

void CarrierStrikeGroup::Render() const {
	StrikeGroup.Render();
}

bool CarrierStrikeGroup::GetReady() const { // Returns [true] if all Ships have been placed.
	return StrikeGroup.ready;
}
