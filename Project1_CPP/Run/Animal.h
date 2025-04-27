#pragma once
#include "Plant.h"


class Animal : public Organism {
protected:
	Position DefaultAction(int Movement);
public:
	Animal(Organism*** world) : Organism(world) {
		prevPosition = position;
	};
	Animal(Organism*** world, Position pos) : Organism(world, pos) {
		prevPosition = position;
	};
	int collision(Organism* OtherOrganism) override;
	Position action() override;
	~Animal() { World = nullptr; };
};

/* returns 3 - if multiplication, returns 2 - if deflection, return 1 if won, return DIR_LEFT if lost. */
/* Collision is performed by the victim of the attack, the otherOrganism is the one that is already in the position */
// turtle.collision(WOLF) <- wolf came to that collumn => DEFENSE
// Human.collision(Antelope) -> ORG_TRYESCAPE (human = victim)
int Animal::collision(Organism* OtherOrganism) {
	int Status = 0;

	if (type == OtherOrganism->returnType()) return ORG_MULTIPLICATION;
	if (strength > OtherOrganism->returnStrength()) Status = ORG_WON;
	else Status = ORG_LOST;
	if (OtherOrganism->returnType() == ANTELOPE) {
		int RandomNumber = rand() % 100;
		if (RandomNumber > THE_FLOOR_OF_ANTELOPE_ESCAPE) {
			if (Status == ORG_WON) return ORG_ATTACKERTRYESCAPE_WON;
			else return ORG_ATTACKERTRYESCAPE_LOST;
		};
	};
	return Status;
};

Position Animal::DefaultAction(int Movement) {
	int move = rand() % NUMBEROFPOSIBLEMOVES;	Position new_Position;
	if (move == DIR_LEFT && position.x >= Movement) {
		new_Position = { position.x - Movement, position.y };
	}
	else if (move == DIR_RIGHT && position.x < WORLD_SIZE_N_X - Movement) {
		new_Position = { position.x + Movement, position.y };
	}
	else if (move == DIR_UP && position.y >= Movement) {
		new_Position = { position.x, position.y - Movement };
	}
	else if (move == DIR_DOWN && position.y < WORLD_SIZE_M_Y - Movement) {
		new_Position = { position.x, position.y + Movement };
	}
	else {
		new_Position = { position.x, position.y };
		prevPosition = position;
		return { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	};
	prevPosition = position;
	position = new_Position;
	return prevPosition;
};

/* returns previous Position */
Position Animal::action() {
	return DefaultAction(DEFAULT_MOVEMENT);
};

class Human : public Animal {
private:
	int NumberOfRoundsUntilPossibleActivation = 0;
	bool IsAbilityOn = 0;
public:
	Human(Organism*** world) : Animal(world) {
		strength = HUMAN_STRENGTH;
		initiative = HUMAN_INITIATIVE;
		type = HUMAN;
	};
	Human(Organism*** world, Position pos) : Animal(world, pos) {
		strength = HUMAN_STRENGTH;
		initiative = HUMAN_INITIATIVE;
		type = HUMAN;
	};
	void SpecialAbility();
	void DecreaseAbilityCounter();
	void DecreaseAbility();
	bool IsAbility() { return IsAbilityOn; };
	bool IsPossibleAbilityActivation() { if (NumberOfRoundsUntilPossibleActivation == 0) return 1; else return 0; };
	Position action(int Move);
	~Human() {};
};

void Human::DecreaseAbilityCounter() {
	if (NumberOfRoundsUntilPossibleActivation != 0) NumberOfRoundsUntilPossibleActivation--;
};

void Human::SpecialAbility() {
	if (NumberOfRoundsUntilPossibleActivation == 0 && IsAbilityOn == 0) {
		strength += HUMAN_NUMBER_OF_TURNS_WITH_ABILITY;
		IsAbilityOn = 1;
	};
};

void Human::DecreaseAbility() {
	if (IsAbilityOn) {
		strength -= ABILITY_ROUND_DECREASE;
		if (strength <= HUMAN_STRENGTH) {
			NumberOfRoundsUntilPossibleActivation = NUMBER_OF_ROUND_UNTIL_POSSIBLE_ACTIVATION_OF_ABILITY;
			IsAbilityOn = 0;
		};
	};
};

Position Human::action(int move) {
	Position new_Position;
	if (move == DIR_LEFT && position.x >= DEFAULT_MOVEMENT) {
		new_Position = { position.x - DEFAULT_MOVEMENT, position.y };
	}
	else if (move == DIR_RIGHT && position.x < WORLD_SIZE_N_X - DEFAULT_MOVEMENT) {
		new_Position = { position.x + DEFAULT_MOVEMENT, position.y };
	}
	else if (move == DIR_UP && position.y >= DEFAULT_MOVEMENT) {
		new_Position = { position.x, position.y - DEFAULT_MOVEMENT };
	}
	else if (move == DIR_DOWN && position.y < WORLD_SIZE_M_Y - DEFAULT_MOVEMENT) {
		new_Position = { position.x, position.y + DEFAULT_MOVEMENT };
	}
	else {
		new_Position = { position.x, position.y };
		prevPosition = position;
		return { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	};
	prevPosition = position;
	position = new_Position;
	return prevPosition;
};

class Wolf : public Animal {
public:
	Wolf(Organism*** world) : Animal(world) {
		strength = WOLF_STRENGTH;
		initiative = WOLF_INITIATIVE;
		type = WOLF;
	};
	Wolf(Organism*** world, Position pos) : Animal(world, pos) {
		strength = WOLF_STRENGTH;
		initiative = WOLF_INITIATIVE;
		type = WOLF;
	};
	~Wolf() {};
};

class Sheep : public Animal {
public:
	Sheep(Organism*** world) : Animal(world) {
		strength = SHEEP_STRENGTH;
		initiative = SHEEP_INITIATIVE;
		type = SHEEP;
	};
	Sheep(Organism*** world, Position pos) : Animal(world, pos) {
		strength = SHEEP_STRENGTH;
		initiative = SHEEP_INITIATIVE;
		type = SHEEP;
	};
	~Sheep() {};
};

class Fox : public Animal {
private:
	Position FoxAction(int Movement);
public:
	Fox(Organism*** world) : Animal(world) {
		strength = FOX_STRENGTH;
		initiative = FOX_INITIATIVE;
		type = FOX;
	};
	Fox(Organism*** world, Position pos) : Animal(world, pos) {
		strength = FOX_STRENGTH;
		initiative = FOX_INITIATIVE;
		type = FOX;
	};
	Position action() override;
	~Fox() {};
};

Position Fox::FoxAction(int Movement) {
	Position new_Position = { NOMOVE_NEGATIVEONE , NOMOVE_NEGATIVEONE };	bool Flag = 1;
	int NumberOfPossibleMoves = NUMBEROFPOSIBLEMOVES, Moves[NUMBEROFPOSIBLEMOVES] = { 0, 1, 2, 3 };
	while (Flag) {
		int RandomNumb = rand() % NumberOfPossibleMoves;
		if (RandomNumb == Moves[0] && position.x >= Movement) {
			if (World[position.x - Movement][position.y] == nullptr) {
				new_Position = { position.x - Movement, position.y };	Flag = 0;
			}
			else {
				if (strength >= World[position.x - Movement][position.y]->returnStrength()) {
					new_Position = { position.x - Movement, position.y };	Flag = 0;
				}
				else { Moves[0] = -1; Moves[1]--; Moves[2]--; Moves[3]--; NumberOfPossibleMoves--; };
			};
		}
		else if (RandomNumb == Moves[1] && position.x < WORLD_SIZE_N_X - Movement) {
			if (World[position.x + Movement][position.y] == nullptr) {
				new_Position = { position.x + Movement, position.y };	Flag = 0;
			}
			else {
				if (strength >= World[position.x + Movement][position.y]->returnStrength()) {
					new_Position = { position.x + Movement, position.y };	Flag = 0;
				}
				else { Moves[1] = -1; Moves[2]--; Moves[3]--; NumberOfPossibleMoves--; };
			};
		}
		else if (RandomNumb == Moves[2] && position.y >= Movement) {
			if (World[position.x][position.y - Movement] == nullptr) {
				new_Position = { position.x, position.y - Movement };	Flag = 0;
			}
			else {
				if (strength >= World[position.x][position.y - Movement]->returnStrength()) {
					new_Position = { position.x, position.y - Movement };	Flag = 0;
				}
				else { Moves[0] = -1; Moves[3]--; NumberOfPossibleMoves--; };
			};
		}
		else if (RandomNumb == Moves[3] && position.y < WORLD_SIZE_M_Y - Movement) {
			if (World[position.x][position.y + Movement] == nullptr) {
				new_Position = { position.x, position.y + Movement };	Flag = 0;
			}
			else {
				if (strength >= World[position.x][position.y + Movement]->returnStrength()) {
					new_Position = { position.x, position.y + Movement };	Flag = 0;
				}
				else { Moves[3] = -1; NumberOfPossibleMoves--; };
			};
		}
		else { Flag = 0; };
		if (NumberOfPossibleMoves <= 0) Flag = 0;
	};
	if (new_Position.x == NOMOVE_NEGATIVEONE) {
		prevPosition = position;
		return { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	};
	prevPosition = position;
	position = new_Position;
	return prevPosition;
};

Position Fox::action() {
	return FoxAction(DEFAULT_MOVEMENT);
};

class Turtle : public Animal {
public:
	Turtle(Organism*** world) : Animal(world) {
		strength = TURTLE_STRENGTH;
		initiative = TURTLE_INITIATIVE;
		type = TURTLE;
	};
	Turtle(Organism*** world, Position pos) : Animal(world, pos) {
		strength = TURTLE_STRENGTH;
		initiative = TURTLE_INITIATIVE;
		type = TURTLE;
	};
	int collision(Organism* OtherOrganism) override;
	Position action() override;
	~Turtle() {};
};

// turtle.collision(WOLF) <- wolf came to that collumn => DEFENSE
int Turtle::collision(Organism* OtherOrganism) {
	if (type == OtherOrganism->returnType()) return ORG_MULTIPLICATION;
	if (OtherOrganism->returnStrength() > TURTLE_DEFENSE) return ORG_LOST;
	return ORG_DEFLECTED;
};

Position Turtle::action() {
	int RandomNumb = rand() % 100;
	if (RandomNumb < THE_FLOOR_OF_TURTLE_MOVEMENT) {
		prevPosition = position;
		return { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	}
	else return DefaultAction(DEFAULT_MOVEMENT);
};

class Antelope : public Animal {
public:
	Antelope(Organism*** world) : Animal(world) {
		strength = ANTELOPE_STRENGTH;
		initiative = ANTELOPE_INITIATIVE;
		type = ANTELOPE;
	};
	Antelope(Organism*** world, Position pos) : Animal(world, pos) {
		strength = ANTELOPE_STRENGTH;
		initiative = ANTELOPE_INITIATIVE;
		type = ANTELOPE;
	};
	Position action() override;
	int collision(Organism* OtherOrganism) override;
	~Antelope() {};
};

Position Antelope::action() {
	return DefaultAction(ANTELOPE_MOVEMENT);
};

// Antelope.collision(Wolf) <- Wolf is the attacker, we are wolf
int Antelope::collision(Organism* OtherOrganism) {
	int Status = 0;
	int RandomNumber = rand() % 100;

	if (type == OtherOrganism->returnType()) return ORG_MULTIPLICATION;

	if (strength > OtherOrganism->returnStrength()) return ORG_WON;
	return ORG_LOST;

	if (strength > OtherOrganism->returnStrength()) Status = ORG_WON;
	else Status = ORG_LOST;
	if (RandomNumber > THE_FLOOR_OF_ANTELOPE_ESCAPE) {
		if (Status == ORG_WON) return ORG_VICTIMTRYESCAPE_WON; /* VICTIMTRYESCAPE */
		else return ORG_VICTIMTRYESCAPE_LOST;
	};
};

