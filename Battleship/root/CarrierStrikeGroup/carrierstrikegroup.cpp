// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "carrierstrikegroup.h"

Ships::Ships(std::vector<glm::vec3> defPos) : AircraftCarrier("Assets/Sprites/carrier.png", defPos[0]), 
											  Cruiser("Assets/Sprites/cruiser.png", defPos[1]),
											  Destroyer1("Assets/Sprites/destroyer.png", defPos[2]), 
											  Destroyer2("Assets/Sprites/destroyer.png", defPos[3]),
											  Supply("Assets/Sprites/supply.png", defPos[4]),
											  Submarine("Assets/Sprites/submarine.png", defPos[5]) {}

void Ships::Update(bool setup) {

	AircraftCarrier.Update(setup);
	Cruiser.Update(setup);
	Destroyer1.Update(setup);
	Destroyer2.Update(setup);
	Supply.Update(setup);
	Submarine.Update(setup);
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

void CarrierStrikeGroup::Update(bool setup) {
	StrikeGroup.Update(setup);
}

void CarrierStrikeGroup::Render() const {
	StrikeGroup.Render();
}

bool CarrierStrikeGroup::GetReady() const {
	return ready;
}
