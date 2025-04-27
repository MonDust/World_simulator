#pragma once
#include "TheWindowsConsole.h"

string ReturnTheOrganismName(char Type) {
	switch (Type) {
	case HUMAN:
		return HUMAN_S; break;
	case WOLF:
		return WOLF_S; break;
	case SHEEP:
		return SHEEP_S; break;
	case FOX:
		return FOX_S; break;
	case TURTLE:
		return TURTLE_S; break;
	case ANTELOPE:
		return ANTELOPE_S;	break;
	case GRASS:
		return GRASS_S;	break;
	case SOWTHISTLE:
		return SOWTHISTLE_S; break;
	case GUARANA:
		return GUARANA_S; break;
	case BELLADONNA:
		return BELLADONNA_S; break;
	case HOGWEED:
		return HOGWEED_S; break;
	default:
		return (string)"UNKNOWN"; break;
	};
};

class Organism {
protected:
	int strength = DEFAULT_STRENGTH, initiative = DEFAULT_INITIATIVE;
	char type = NO_TYPE; /* + - no exact type */
	bool IsAnimal = 1;
	Position position = { 0, 0 }, prevPosition = { 0, 0 };

	Organism*** World = nullptr;
	Organism(Organism*** world) {
		World = world;
		position = { rand() % WORLD_SIZE_N_X, rand() % WORLD_SIZE_M_Y };
	};
	Organism(Organism*** world, Position PositionOfOrganism) {
		World = world;
		position = PositionOfOrganism;
	};
public:
	virtual Position action() = 0;

	/* OtherOrganism = attacker, this = victim */
	virtual int collision(Organism* OtherOrganism) = 0;

	Position FindNonOccupiedPosition(Position PositionOfOrganism);
	Position FindNonOccupiedPosition();
	Position DoesOrganismMultiply(Organism * SecondOrganism);
	void MoveOrganism(Position NewPosition);
	void MoveOrganism();
	Position CheckIfNotOccupiedPosition(Position pos);
	Position CheckIfNotOccupiedPosition();

	void IncreaseStrength(int StrengthPlus);

	/* Returns 1 If animal, 0 if Plant */
	bool returnIsAnimal() { return IsAnimal; };
	char returnType() { return type; };
	int returnStrength() { return strength; };
	int returnInitiative() { return initiative; };
	Position returnPosition() { return position; };
	void ChangePositon(Position NewPosition) { prevPosition = position; position = NewPosition; };
	Position returnPreviousPosition() { return prevPosition; };
};

void Organism::IncreaseStrength(int StrengthPlus) {
	strength += StrengthPlus;
};

/* Finds the nonoccupied position in the world  (close to the Organism) */
Position Organism::FindNonOccupiedPosition(Position PositionOfOrganism) {
	if (PositionOfOrganism.x < WORLD_SIZE_N_X - DEFAULT_MOVEMENT) {
		if (World[PositionOfOrganism.x + DEFAULT_MOVEMENT][PositionOfOrganism.y] == nullptr) {
			return { PositionOfOrganism.x + DEFAULT_MOVEMENT, PositionOfOrganism.y };
		};
	}
	if (PositionOfOrganism.x >= DEFAULT_MOVEMENT) {
		if (World[PositionOfOrganism.x - DEFAULT_MOVEMENT][PositionOfOrganism.y] == nullptr) {
			return { PositionOfOrganism.x - DEFAULT_MOVEMENT, PositionOfOrganism.y };
		};
	}
	if (PositionOfOrganism.y < WORLD_SIZE_M_Y - DEFAULT_MOVEMENT) {
		if (World[PositionOfOrganism.x][PositionOfOrganism.y + DEFAULT_MOVEMENT] == nullptr) {
			return { PositionOfOrganism.x, PositionOfOrganism.y + DEFAULT_MOVEMENT };
		};
	}
	if (PositionOfOrganism.y >= DEFAULT_MOVEMENT) {
		if (World[PositionOfOrganism.x][PositionOfOrganism.y - DEFAULT_MOVEMENT] == nullptr) {
			return { PositionOfOrganism.x, PositionOfOrganism.y - DEFAULT_MOVEMENT };
		};
	};

	return { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
};

/* Finds the nonoccupied position in the world  (close to the Organism) */
Position Organism::FindNonOccupiedPosition() {
	return FindNonOccupiedPosition(position);
};

/* Returns { -1, -1 } if Organism does not multiply, otherwise it returns the position of a new animal */
Position Organism::DoesOrganismMultiply(Organism* SecondOrganism) {
	Position NewPosition = { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	int RandomDoesOrgMultiplies = rand() % 100;

	if (RandomDoesOrgMultiplies < MULTIPLICATIONTRESHHOLD) {
		NewPosition = FindNonOccupiedPosition(position);
		if (NewPosition.x != NOMOVE_NEGATIVEONE) {
			return NewPosition;
		}
		else {
			NewPosition = FindNonOccupiedPosition(SecondOrganism->returnPosition());
			return NewPosition;
		};
	};
	return NewPosition;
};

/* Move the Organism in the world */
void Organism::MoveOrganism() {
	World[prevPosition.x][prevPosition.y] = nullptr;
	World[position.x][position.y] = this;
};

/* Does not delete the Organism from world */
void Organism::MoveOrganism(Position NewPosition) {
	//World[prevPosition.x][prevPosition.y] = nullptr;
	World[NewPosition.x][NewPosition.y] = this;
	ChangePositon(NewPosition);
};

/* Check if the provided position is not occupied, returns { -1, -1} if occupied, otherwise returns the position */
Position Organism::CheckIfNotOccupiedPosition(Position pos) {
	if (World[pos.x][pos.y] == nullptr) return pos;
	return { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
};

Position Organism::CheckIfNotOccupiedPosition() {
	return CheckIfNotOccupiedPosition(position);
};
