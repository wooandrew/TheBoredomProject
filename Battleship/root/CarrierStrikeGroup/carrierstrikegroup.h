// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef CARRIER_STRIKE_GROUP
#define CARRIER_STRIKE_GROUP

#include "../lib.h"
#include "ship.h"

struct Ships {

	Ship AircraftCarrier;
	Ship Cruiser;
	Ship Destroyer1;
	Ship Destroyer2;
	Ship Supply;
	Ship Submarine;

	Ships(std::vector<glm::vec3> defPos);

	void Update(bool setup = false);
	void Render() const;
};

class CarrierStrikeGroup {

public:

	CarrierStrikeGroup(std::vector<glm::vec3> defPos);

	void Update(bool setup = false);
	void Render() const;

	bool GetReady() const;

private:

	bool ready;
	Ships StrikeGroup;
};

typedef CarrierStrikeGroup CSG;

#endif // !CARRIER_STRIKE_GROUP

