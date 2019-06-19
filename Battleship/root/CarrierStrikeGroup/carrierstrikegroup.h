// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef CARRIER_STRIKE_GROUP
#define CARRIER_STRIKE_GROUP

#include "../lib.h"

#include "ship.h"
#include "../Game/game.h"

struct Ships {

	Ship AircraftCarrier;
	Ship Cruiser;
	Ship Destroyer1;
	Ship Destroyer2;
	Ship Supply;
	Ship Submarine;

	bool ready;

	Ships();
	Ships(std::vector<glm::vec3> defPos, bool full = false);

	void Update(Grid& _grid, bool setup = false);
	void Render() const;
	void Reset();

	void Assemble(std::vector<glm::vec3> defPos, std::vector<std::string> _vRotations = std::vector<std::string> { "0", "0", "0", "0", "0", "0" });
};

class CarrierStrikeGroup {

public:

	CarrierStrikeGroup();
	CarrierStrikeGroup(std::vector<glm::vec3> defPos, bool full = false);

	void Update(Grid& _grid, bool setup = false);
	void Render() const;
	void Reset();

	void Assemble(std::vector<glm::vec3> defPos);
	void Assemble(Grid& _grid, std::string _placedids, std::string _rotations);

	bool GetReady() const;
	std::string GetPlacedIDs() const;
	std::string GetRotations();

private:

	Ships StrikeGroup;
	std::string PlacedIDs;
};

typedef CarrierStrikeGroup CSG;

#endif // !CARRIER_STRIKE_GROUP

