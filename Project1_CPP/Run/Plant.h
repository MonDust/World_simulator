#pragma once
#include "Organism.h"

class Plant :public Organism {
public:
	Plant(Organism*** world): Organism(world) {
		IsAnimal = 0;
	};
	Plant(Organism*** world, Position pos) : Organism(world, pos) {
		IsAnimal = 0;
	};
	int collision(Organism* OtherOrganism) override;
	Position action() override;
	~Plant() { World = nullptr; };
};

/* OtherOrganism = attacker, this = victim */
int Plant::collision(Organism* OtherOrganism) {
	if (strength > OtherOrganism->returnStrength()) ORG_WON;
	return ORG_LOST;
};

Position Plant::action() {
	Position new_Position = { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	int ProbabilityOfSpread = rand() % 100;

	if (ProbabilityOfSpread < THE_FLOOR_OF_SPREAD) {
		int SpreadDirection = rand() % NUMBEROFPOSIBLEMOVES;

		if (SpreadDirection == DIR_LEFT && position.x >= DEFAULT_SPREAD) {
			new_Position = CheckIfNotOccupiedPosition({ position.x - DEFAULT_SPREAD, position.y });
		}
		else if (SpreadDirection == DIR_RIGHT && position.x < WORLD_SIZE_N_X - DEFAULT_SPREAD) {
			new_Position = CheckIfNotOccupiedPosition({ position.x + DEFAULT_SPREAD, position.y });
		}
		else if (SpreadDirection == DIR_UP && position.y >= DEFAULT_SPREAD) {
			new_Position = CheckIfNotOccupiedPosition({ position.x, position.y - DEFAULT_SPREAD });
		}
		else if (SpreadDirection == DIR_DOWN && position.y < WORLD_SIZE_M_Y - DEFAULT_SPREAD) {
			new_Position = CheckIfNotOccupiedPosition({ position.x, position.y + DEFAULT_SPREAD });
		}; };
	return new_Position;
};


class Grass : public Plant {
public:
	Grass(Organism*** world) : Plant(world) {
		strength = GRASS_STRENGTH;
		type = GRASS;
	};
	Grass(Organism*** world, Position pos) : Plant(world, pos) {
		strength = GRASS_STRENGTH;
		type = GRASS;
	};
	~Grass() {};
};

class SowThistle : public Plant {
public:
	SowThistle(Organism*** world) : Plant(world) {
		strength = SOWTHISTLE_STRENGTH;
		type = SOWTHISTLE;
	};
	SowThistle(Organism*** world, Position pos) : Plant(world, pos) {
		strength = SOWTHISTLE_STRENGTH;
		type = SOWTHISTLE;
	};
	Position action() override;
	~SowThistle() {};
};

Position SowThistle::action() {
	Position new_Position = { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	for (int i = 0; i < ATTEMPTS_OF_SPREAD_SOWTHISTLE; i++) {
		new_Position = Plant::action();
		if (new_Position.x != NOMOVE_NEGATIVEONE) return new_Position;
	};
	return new_Position;
};

class Guarana : public Plant {
public:
	Guarana(Organism*** world) : Plant(world) {
		strength = GUARANA_STRENGTH;
		type = GUARANA;
	};
	Guarana(Organism*** world, Position pos) : Plant(world, pos) {
		strength = GUARANA_STRENGTH;
		type = GUARANA;
	};
	int collision(Organism* OtherOrganism) override;
	~Guarana() {};
};

int Guarana::collision(Organism* OtherOrganism) {
	OtherOrganism->IncreaseStrength(STRENGTH_INCREASE_GUARANA);
	return ORG_LOST;
};

class Belladonna : public Plant {
public:
	Belladonna(Organism*** world) : Plant(world) {
		strength = BELLADONNA_STRENGTH;
		type = BELLADONNA;
	};
	Belladonna(Organism*** world, Position pos) : Plant(world, pos) {
		strength = BELLADONNA_STRENGTH;
		type = BELLADONNA;
	};
	~Belladonna() {};
};


class Hogweed : public Plant {
public:
	Hogweed(Organism*** world) : Plant(world) {
		strength = HOGWEED_STRENGTH;
		type = HOGWEED;
	};
	Hogweed(Organism*** world, Position pos) : Plant(world, pos) {
		strength = HOGWEED_STRENGTH;
		type = HOGWEED;
	};
	int collision(Organism* OtherOrganism) override;
	~Hogweed() {};
};


int Hogweed::collision(Organism* OtherOrganism) {
	return ORG_WON;
};
