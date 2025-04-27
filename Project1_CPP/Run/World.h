#pragma once
#include "Animal.h"

#define SAVESCREEN_X	0
#define SAVESCREEN_Y	2

/* ----------------------------------------------- THE VARAIBLES FOR NONRANDOM INITIALIZATION -------------------------------------------------------- */
#define NR_WOLF		0		
#define NR_SHEEP	0	
#define NR_FOX		0
#define NR_TURTLE	7
#define NR_ANTELOPE	0
#define NR_GRASS		1
#define NR_SOWTHISTLE	0
#define NR_GUARANA		0
#define NR_BELLADONNA	0
#define NR_HOGWEED		0


const int NonRandomListOfOrganisms[DEFAULT_NUMBER_OF_ORGANISMS] = { NR_WOLF, NR_SHEEP, NR_FOX, NR_TURTLE, NR_ANTELOPE, NR_GRASS, NR_SOWTHISTLE, NR_GUARANA, NR_BELLADONNA, NR_HOGWEED };

/* The world in which Organisms reside */
class World {
private:
	Organism*** VirWorld; /* NxM table with organisms placed */
	Human* MyHuman;
	vector<Organism*> ListOfOrganisms;
	int CurrentNumberOfOrganisms = 0;
	int InitiativesList[NUMBER_OF_INITIATIVES] = { HUMAN_INITIATIVE, WOLF_INITIATIVE, SHEEP_INITIATIVE, FOX_INITIATIVE, TURTLE_INITIATIVE, ANTELOPE_INITIATIVE, DEFAULT_INITIATIVE };
	Position CommenterPosition;
	vector<string> CommentatorList;

	void DeleteHuman();
	void  DeleteAnimal(Organism* OrganismToDel);
	void KillAround(Position StartPosition);

	void HumanProcedure(int Move);
	void OrganismProcedure(Organism * CurrentOrganism, int OrganismIndex);
	void InitProcdedure(Organism* CurrentOrganism, int OrganismIndex);
	void CollisionProcedure(int ResultOfCollision, Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex);
	
	void AddDefaultOrganisms();
	void AddNonRandomOrganism(int OrganismNumber);
	void AddNonRandomOrganism_toPos(char OrganismType, Position Pos);
	void AddOrganismToWorld(Position pos, Organism* NewOrganism);

	void DrawWorld(Position WorldShift);
	int FindIndexOfVector(Organism* Address);

	void VictimLost(Organism* AttackerOrganism, Organism* VictimOrganism);
	void VictimWon(Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex);
	void Multiplication(Organism* AttackerOrganism, Organism* VictimOrganism);
	void VictimEscape(int Result, Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex);
	void AttackerEscape(int Result, Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex);
	void InitWorld();
public:
	World();
	Organism*** returnWorld() { return VirWorld; };

	void SaveFile();
	void LoadFile();

	void TurnOnSuperPower();
	void InitializeOrganisms();
	void InitializeOrganisms_NonRandom();
	void NextStep(int HumanMove);

	void Commenter();
	void CleanWorld();
	void Print(Position WorldShift);
	~World();
};

void World::InitWorld() {
	CleanWorld();
	int size = (int)ListOfOrganisms.size();
	for (int i = 0; i < size; i++) {
		VirWorld[ListOfOrganisms[i]->returnPosition().x][ListOfOrganisms[i]->returnPosition().y] = ListOfOrganisms[i];
	};
	if (MyHuman != nullptr) {
		VirWorld[MyHuman->returnPosition().x][MyHuman->returnPosition().y] = MyHuman;
	};
};

void World::LoadFile() {
	ListOfOrganisms.clear();
	if (MyHuman != nullptr) {
		delete MyHuman; MyHuman = nullptr;
	};
	CommentatorList.clear();
	CleanWorld();
	system("CLS");
	gotoxy(SAVESCREEN_X, SAVESCREEN_Y+2);
	_setCursor(SOLIDCURSOR);
	vector<string> filenames = getAllFilesWithinFolder();
	int NumberOfFiles = filenames.size();
	for (int i = 0; i < NumberOfFiles; i++) {
		cout << i <<": " << filenames[i] << "\n";
	};
	gotoxy(SAVESCREEN_X, SAVESCREEN_Y);
	int Number;
	cin >> Number;
	if (Number < NumberOfFiles && Number >= 0) {
		FILE* file;
		fopen_s(&file, filenames[Number].c_str(), "r");
		if (file == NULL) perror("Failed to open file: ");
		else {
			int SizeOfList = (int)ListOfOrganisms.size();
			int x, y;
			char c;
			fscanf_s(file, "%d %d", &x, &y);
			fgetc(file);
			c = fgetc(file);
			if (c == HUMAN) {
				MyHuman = new Human(VirWorld, { x,y });
				VirWorld[x][y] = MyHuman;
			}
			else AddNonRandomOrganism_toPos(c, { x,y });
			while (TRUE) {
				if (fscanf_s(file, "%d %d", &x, &y) == EOF) break;
				fgetc(file);
				c = fgetc(file);
				AddNonRandomOrganism_toPos(c, {x,y});
				//if (feof(file))  break;
			};
			fclose(file);
		};
	};
	CurrentNumberOfOrganisms = ListOfOrganisms.size();
};

#define _CRT_SECURE_NO_WARNINGS

void World::SaveFile() {
	system("CLS");
	gotoxy(SAVESCREEN_X, SAVESCREEN_Y);
	_setCursor(SOLIDCURSOR);
	string Savename;	cin >> Savename;
	if (Savename.empty()) {
		Savename = "default";
	};
	FILE* file;
	fopen_s(&file, (Savename + ".txt").c_str(), "w+");
	if (file == NULL) perror("Failed to open file: ");
	else {
		if (MyHuman != nullptr) {
			fprintf_s(file, "%d %d %c\n", MyHuman->returnPosition().x, MyHuman->returnPosition().y, MyHuman->returnType());
		};
		int SizeOfList = (int)ListOfOrganisms.size();
		for (int i = 0; i < SizeOfList; i++) {
			fprintf_s(file, "%d %d %c\n", ListOfOrganisms[i]->returnPosition().x, ListOfOrganisms[i]->returnPosition().y, ListOfOrganisms[i]->returnType());
		};
		fclose(file);
	};
};

void World::TurnOnSuperPower() {
	if (MyHuman != nullptr) {
		CommentatorList.clear();
		MyHuman->SpecialAbility();
		if (MyHuman->returnStrength() == HUMAN_STRENGTH + HUMAN_NUMBER_OF_TURNS_WITH_ABILITY) {
			CommentatorList.push_back("SpecialAbility activated");
		}
		else if (MyHuman->returnStrength() > HUMAN_STRENGTH) {
			CommentatorList.push_back("SpecialAbility already active");
		}
		else {
			CommentatorList.push_back("Cannot activate SpecialAbility");
		};
		Commenter();
	};
};


/* Commenter shouting what is going on in the world */
void World::Commenter() {
	int Size = (int)CommentatorList.size();
	for (int i = 0; i < Size; i++) {
		gotoxy(CommenterPosition.x,CommenterPosition.y+i);
		cout << CommentatorList[i];
	};
	_setCursor(NOCURSOR);
};

// Human.collision(Antelope) <- Antelope attacker
// Antelope.collision(Human) <- Human attacker
/* Procedure for when Victim Loses */
void World::VictimLost(Organism* AttackerOrganism, Organism* VictimOrganism) {
	string AttackerName = ReturnTheOrganismName(AttackerOrganism->returnType());
	string VictimName = ReturnTheOrganismName(VictimOrganism->returnType());
	CommentatorList.push_back("The Attacker: " + AttackerName + " won with: " + VictimName);

	int VictimIndex = -1;
	AttackerOrganism->MoveOrganism();
	if (VictimOrganism->returnType() == HUMAN) {
		DeleteHuman();
	}
	else {
		VictimIndex = FindIndexOfVector(VictimOrganism);
		if (VictimIndex != -1) {
			ListOfOrganisms.erase(ListOfOrganisms.begin() + VictimIndex);
			CurrentNumberOfOrganisms--;
		};
	};
	VirWorld[AttackerOrganism->returnPreviousPosition().x][AttackerOrganism->returnPreviousPosition().y] = nullptr;
	VirWorld[AttackerOrganism->returnPosition().x][AttackerOrganism->returnPosition().y] = AttackerOrganism;
};

// Human.collision(Antelope) <- Antelope attacker
// Antelope.collision(Human) <- Human attacker
/* Procedure for when Victim Won */
void World::VictimWon(Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex) {
	string AttackerName = ReturnTheOrganismName(AttackerOrganism->returnType());
	string VictimName = ReturnTheOrganismName(VictimOrganism->returnType());
	CommentatorList.push_back("The Attacker: "+AttackerName+" lost to: "+VictimName);

	VirWorld[AttackerOrganism->returnPreviousPosition().x][AttackerOrganism->returnPreviousPosition().y] = nullptr;
	if (AttackerOrganism->returnType() == HUMAN) {
		DeleteHuman();
	}
	else {
		ListOfOrganisms.erase(ListOfOrganisms.begin() + AttackerIndex);
		CurrentNumberOfOrganisms--;
	};
	if (!VictimOrganism->returnIsAnimal()) {
		int VictimIndex = FindIndexOfVector(VictimOrganism);
		VirWorld[VictimOrganism->returnPosition().x][VictimOrganism->returnPosition().y] = nullptr;
		ListOfOrganisms.erase(ListOfOrganisms.begin() + VictimIndex);
		CurrentNumberOfOrganisms--;
	}
	else VirWorld[VictimOrganism->returnPosition().x][VictimOrganism->returnPosition().y] = VictimOrganism;
};

/* the multiplying when two animals meet */
void World::Multiplication(Organism* AttackerOrganism, Organism* VictimOrganism) {
	string AttackerName = ReturnTheOrganismName(AttackerOrganism->returnType());
	Position NewPosition = VictimOrganism->DoesOrganismMultiply(AttackerOrganism);
	if (NewPosition.x != NOMOVE_NEGATIVEONE) {
		CommentatorList.push_back("The " + AttackerName + " multiplied");
		AddNonRandomOrganism_toPos(VictimOrganism->returnType(), NewPosition);
	};
};

/* Procedure if Antelope Victim Escapes */
void World::VictimEscape(int Result, Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex) {
	Position NewPosition = VictimOrganism->FindNonOccupiedPosition();
	if (NewPosition.x != NOMOVE_NEGATIVEONE) {
		string VictimName = ReturnTheOrganismName(VictimOrganism->returnType());
		string AttackerName = ReturnTheOrganismName(AttackerOrganism->returnType());
		CommentatorList.push_back("The "+VictimName + " attacked by: " + AttackerName + " escaped");
		VictimOrganism->MoveOrganism(NewPosition);
		AttackerOrganism->MoveOrganism();
	}
	else {
		if (Result == ORG_VICTIMTRYESCAPE_LOST) VictimLost(AttackerOrganism, VictimOrganism);
		else VictimWon(AttackerOrganism, VictimOrganism, AttackerIndex);
	};
};

/* Procedure if Antelope Attacker Escapes */
void World::AttackerEscape(int Result, Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex) {
	Position NewPosition = AttackerOrganism->FindNonOccupiedPosition();
	if (NewPosition.x != NOMOVE_NEGATIVEONE) {
		string AttackerName = ReturnTheOrganismName(AttackerOrganism->returnType());
		string VictimName = ReturnTheOrganismName(VictimOrganism->returnType());
		CommentatorList.push_back("The Attacker: "+AttackerName+" escaped from: "+VictimName);
		VirWorld[AttackerOrganism->returnPreviousPosition().x][AttackerOrganism->returnPreviousPosition().y] = nullptr;
		AttackerOrganism->MoveOrganism(NewPosition);
	}
	else {
		if (Result == ORG_ATTACKERTRYESCAPE_LOST) VictimLost(AttackerOrganism, VictimOrganism);
		else VictimWon(AttackerOrganism, VictimOrganism, AttackerIndex);
	};
};

/* Procedure when two Organism collide */
void World::CollisionProcedure(int ResultOfCollision, Organism* AttackerOrganism, Organism* VictimOrganism, int AttackerIndex) {

	switch (ResultOfCollision) {
	case ORG_LOST:
		VictimLost(AttackerOrganism, VictimOrganism);
		break;
	case ORG_WON:
		VictimWon(AttackerOrganism, VictimOrganism, AttackerIndex);
		break;
	case ORG_DEFLECTED:
		AttackerOrganism->ChangePositon(AttackerOrganism->returnPreviousPosition());
		break;
	case ORG_MULTIPLICATION:
		Multiplication(AttackerOrganism, VictimOrganism);
		break;
	case ORG_ATTACKERTRYESCAPE_LOST: /* Human.collision(Antelope) <- Human = victim, Antelope = attacker */
	case ORG_ATTACKERTRYESCAPE_WON:
		AttackerEscape(ResultOfCollision, AttackerOrganism, VictimOrganism, AttackerIndex);
		break;
	case ORG_VICTIMTRYESCAPE_LOST:
	case ORG_VICTIMTRYESCAPE_WON:
		VictimEscape(ResultOfCollision, AttackerOrganism, VictimOrganism, AttackerIndex);
		break;
	};
};

/* delete the Human */
void World::DeleteHuman() {
	//VirWorld[MyHuman->returnPosition().x][MyHuman->returnPosition().y] = nullptr;
	delete MyHuman;
	MyHuman = nullptr;
};

/* delete the NonHuman Organism */
void World::DeleteAnimal(Organism* OrganismToDel) {
	int Index = NOTFOUND_MINUS1;
	Position OrganismPosition = OrganismToDel->returnPosition();
	if (VirWorld[OrganismPosition.x][OrganismPosition.y]->returnIsAnimal()) {
		VirWorld[OrganismPosition.x][OrganismPosition.y] = nullptr;
		string OrgName = ReturnTheOrganismName(OrganismToDel->returnType());
		CommentatorList.push_back("The "+OrgName+" died");
		if (OrganismToDel->returnType() == HUMAN) {
			DeleteHuman();
		}
		else {
			Index = FindIndexOfVector(OrganismToDel);
			if (Index != NOTFOUND_MINUS1) {
				ListOfOrganisms.erase(ListOfOrganisms.begin() + Index);
				CurrentNumberOfOrganisms--;
			};};};
};

void World::KillAround(Position StartPosition) {
	if (StartPosition.x < WORLD_SIZE_N_X - DEFAULT_MOVEMENT) {
		if (VirWorld[StartPosition.x + DEFAULT_MOVEMENT][StartPosition.y] != nullptr) {
			DeleteAnimal(VirWorld[StartPosition.x + DEFAULT_MOVEMENT][StartPosition.y]);
		};
	};
	if (StartPosition.x >= DEFAULT_MOVEMENT) {
		if (VirWorld[StartPosition.x - DEFAULT_MOVEMENT][StartPosition.y] != nullptr) {
			DeleteAnimal(VirWorld[StartPosition.x - DEFAULT_MOVEMENT][StartPosition.y]);
		};
	};
	if (StartPosition.y < WORLD_SIZE_M_Y - DEFAULT_MOVEMENT) {
		if (VirWorld[StartPosition.x][StartPosition.y + DEFAULT_MOVEMENT] != nullptr) {
			DeleteAnimal(VirWorld[StartPosition.x][StartPosition.y + DEFAULT_MOVEMENT]);
		};
	};
	if (StartPosition.y >= DEFAULT_MOVEMENT) {
		if (VirWorld[StartPosition.x][StartPosition.y - DEFAULT_MOVEMENT] != nullptr) {
			DeleteAnimal(VirWorld[StartPosition.x][StartPosition.y - DEFAULT_MOVEMENT]);
		}; };
};

void World::InitProcdedure(Organism* CurrentOrganism, int OrganismIndex) {
	int ResultOfCollision = 0;
	Position OrgPos = CurrentOrganism->returnPosition();
	Organism* OtherOrganism = VirWorld[OrgPos.x][OrgPos.y];
	if (CurrentOrganism->CheckIfNotOccupiedPosition().x == NOMOVE_NEGATIVEONE) {
		ResultOfCollision = OtherOrganism->collision(CurrentOrganism);
		CollisionProcedure(ResultOfCollision, CurrentOrganism, OtherOrganism, OrganismIndex);
	}
	else {
		CurrentOrganism->MoveOrganism();
	};
};

void World::HumanProcedure(int Move) {
	if (Move != NO_MOVE) {
		Position ReturnPosition = MyHuman->action(Move);
		if (ReturnPosition.x != NOMOVE_NEGATIVEONE) {
			InitProcdedure(MyHuman, -1);
		};
	};
};

void World::OrganismProcedure(Organism* CurrentOrganism, int OrganismIndex) {
	Position ReturnPosition = CurrentOrganism->action();

	if (ReturnPosition.x != NOMOVE_NEGATIVEONE) {
		if (CurrentOrganism->returnIsAnimal()) {
			InitProcdedure(CurrentOrganism, OrganismIndex);
		}
		else { /* IF PLANT */
			string OrgName = ReturnTheOrganismName(CurrentOrganism->returnType());
			CommentatorList.push_back("The " + OrgName + " spread");
			AddNonRandomOrganism_toPos(CurrentOrganism->returnType(), ReturnPosition);
		};
	};
	if (CurrentOrganism->returnType() == HOGWEED) {
		KillAround(CurrentOrganism->returnPosition());
	};
};

void World::NextStep(int HumanMove) {
	CommentatorList.clear();
	Position ReturnPosition = { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
	int CurrentInitiative = -1;
	CurrentNumberOfOrganisms = (int)ListOfOrganisms.size();

	for (int j = 0; j < NUMBER_OF_INITIATIVES; j++) {
		if (InitiativesList[j] != CurrentInitiative) {
			if (MyHuman != nullptr) {
				if (MyHuman->returnInitiative() == InitiativesList[j]) {
					HumanProcedure(HumanMove);
				};
			};
			Organism* CurrentOrganism;
			int i = 0;
			while(i < CurrentNumberOfOrganisms) {
				CurrentOrganism = ListOfOrganisms[i];
				if (CurrentOrganism->returnInitiative() == InitiativesList[j]) {
					OrganismProcedure(CurrentOrganism, i);

					i = FindIndexOfVector(CurrentOrganism);
				};
				i++;
			};
			CurrentInitiative = InitiativesList[j];
			ReturnPosition = { NOMOVE_NEGATIVEONE, NOMOVE_NEGATIVEONE };
		};
	};
	if (MyHuman != nullptr) {
		MyHuman->DecreaseAbility();
		MyHuman->DecreaseAbilityCounter();
	};
	InitWorld();
};

/* Add Organism into 2D array */
void World::AddOrganismToWorld(Position pos, Organism* NewOrganism) {
	VirWorld[pos.x][pos.y] = NewOrganism;
};

/* Try to add all Organism in the number of One */
void World::AddDefaultOrganisms() {
	for (int i = 0; i < DEFAULT_NUMBER_OF_ORGANISMS; i++) {
		AddNonRandomOrganism(i);
	};
};


/* Adding Organism based the Organism Type and provided position */
void World::AddNonRandomOrganism_toPos(char OrganismType, Position Pos) {
	Organism* NewOrganism;
	switch (OrganismType) {
	case WOLF:
		NewOrganism = new Wolf(VirWorld, Pos);
		break;
	case SHEEP:
		NewOrganism = new Sheep(VirWorld, Pos);
		break;
	case FOX:
		NewOrganism = new Fox(VirWorld, Pos);
		break;
	case TURTLE:
		NewOrganism = new Turtle(VirWorld, Pos);
		break;
	case ANTELOPE:
		NewOrganism = new Antelope(VirWorld, Pos);
		break;
	case GRASS:
		NewOrganism = new Grass(VirWorld, Pos);
		break;
	case SOWTHISTLE:
		NewOrganism = new SowThistle(VirWorld, Pos);
		break;
	case GUARANA:
		NewOrganism = new Guarana(VirWorld, Pos);
		break;
	case BELLADONNA:
		NewOrganism = new Belladonna(VirWorld, Pos);
		break;
	default:
		NewOrganism = new Hogweed(VirWorld, Pos);
		break;
	};
	if (NewOrganism->CheckIfNotOccupiedPosition().x != NOMOVE_NEGATIVEONE) {
		VirWorld[NewOrganism->returnPosition().x][NewOrganism->returnPosition().y] = NewOrganism;
		ListOfOrganisms.push_back(NewOrganism);
	}
	else delete NewOrganism; /* CHECK: changed */
};

/* Adding Organism based previously on the randomly chosen number */
void World::AddNonRandomOrganism(int OrganismNumber) {
	Organism* NewOrganism;
	switch (OrganismNumber) {
	case 0:
		NewOrganism = new Wolf(VirWorld);
		break;
	case 1:
		NewOrganism = new Sheep(VirWorld);
		break;
	case 2:
		NewOrganism = new Fox(VirWorld);
		break;
	case 3:
		NewOrganism = new Turtle(VirWorld);
		break;
	case 4:
		NewOrganism = new Antelope(VirWorld);
		break;
	case 5:
		NewOrganism = new Grass(VirWorld);
		break;
	case 6:
		NewOrganism = new SowThistle(VirWorld);
		break;
	case 7:
		NewOrganism = new Guarana(VirWorld);
		break;
	case 8:
		NewOrganism = new Belladonna(VirWorld);
		break;
	default:
		NewOrganism = new Hogweed(VirWorld);
		break;
	};
	if (NewOrganism->CheckIfNotOccupiedPosition().x != NOMOVE_NEGATIVEONE) {
		VirWorld[NewOrganism->returnPosition().x][NewOrganism->returnPosition().y] = NewOrganism;
		ListOfOrganisms.push_back(NewOrganism);
		CurrentNumberOfOrganisms++;
	}
	else delete NewOrganism; /* CHECK: changed */
};

/* Initialize the Organisms in the world */
void World::InitializeOrganisms() {
	int MaxOrganisms = WORLD_SIZE_N_X * WORLD_SIZE_M_Y;
	float Percent = (float)(PERCENTOFMAXORGANISM / 100.0);
	int RandNumber = (int)(MaxOrganisms * Percent + 1);
	int NumberOfOrganisms = rand() % RandNumber;
	int CurOrg = 0;
	int NumberOfIters = 0;

	while (NumberOfOrganisms + DEFAULT_NUMBER_OF_ORGANISMS > MaxOrganisms) NumberOfOrganisms--;
	AddDefaultOrganisms();
	while (NumberOfOrganisms != 0 && NumberOfIters < MAX_NUMBER_OF_ITERATIONS_WHILE_RANDOMAZING) {
		CurOrg = CurrentNumberOfOrganisms;
		int RandomNum = rand() % DEFAULT_NUMBER_OF_ORGANISMS;
		AddNonRandomOrganism(RandomNum);
		if (CurOrg != CurrentNumberOfOrganisms) {
			NumberOfOrganisms--;
		};
		NumberOfIters++;
	};
};

/* Initialize the Organisms in the world */
void World::InitializeOrganisms_NonRandom() {
	int MaxOrganisms = WORLD_SIZE_N_X * WORLD_SIZE_M_Y;
	int CurOrg;
	int IterNumber = 0;

	for (int i = 0; i < DEFAULT_NUMBER_OF_ORGANISMS; i++) {
		for (int j = 0; j < NonRandomListOfOrganisms[i]; j++) {
			CurOrg = CurrentNumberOfOrganisms;
			AddNonRandomOrganism(i);
			if (CurOrg == CurrentNumberOfOrganisms) j--;
			IterNumber++;
			if (IterNumber > MAX_NUMBER_OF_ITERATIONS_WHILE_RANDOMAZING) break;
		};
		if (IterNumber > MAX_NUMBER_OF_ITERATIONS_WHILE_RANDOMAZING) break;
	};
};

/* return -1 if not found, else returns the index of the Organism */
int World::FindIndexOfVector(Organism* Address) {
	int Index = -1;
	auto it = find(ListOfOrganisms.begin(), ListOfOrganisms.end(), Address);

	if (it != ListOfOrganisms.end()) {
		Index = (int)distance(ListOfOrganisms.begin(), it);
	};
	return Index;
};

/* Constructor for world */
World::World() {
	VirWorld = new Organism * *[WORLD_SIZE_N_X];
	for (int i = 0; i < WORLD_SIZE_N_X; i++) {
		VirWorld[i] = new Organism * [WORLD_SIZE_M_Y];
		for (int j = 0; j < WORLD_SIZE_M_Y; j++) {
			VirWorld[i][j] = nullptr;
		};
	};
	MyHuman = new Human(VirWorld);
	VirWorld[MyHuman->returnPosition().x][MyHuman->returnPosition().y] = MyHuman;
	BubbleSort(InitiativesList, NUMBER_OF_INITIATIVES);
	CommenterPosition = { 0, 0 };
};

/* Deconstructor for world */
World::~World() {
	for (int i = 0; i < WORLD_SIZE_N_X; i++) {
		delete[] VirWorld[i];
	};
	delete[] VirWorld;
	if (MyHuman != nullptr) delete MyHuman;
};

void World::DrawWorld(Position WorldShift) {
	Position screenSize = getSizeOfScreen();
	Position PrintWorld = { 0, 0 };
	if (WORLDINCONSOLE_X + (WORLD_SIZE_N_X * 2) > screenSize.x) PrintWorld.x = (screenSize.x - WORLDINCONSOLE_X) / 2;
	else PrintWorld.x = WORLD_SIZE_N_X;
	if (WORLDINCONSOLE_Y + WORLD_SIZE_M_Y > screenSize.y) PrintWorld.y = screenSize.y - WORLDINCONSOLE_Y - 1;
	else PrintWorld.y = WORLD_SIZE_M_Y;
	char type_s[2] = " ";

	for (int i = 0; i < PrintWorld.x; i++) {
		for (int j = 0; j < PrintWorld.y; j++) {
			int coord_x = i + (WorldShift.x / 2), coord_y = j + WorldShift.y;
			if (VirWorld[coord_x][coord_y] == nullptr) _cputs(" ");
			else {
				char CurType = VirWorld[coord_x][coord_y]->returnType();	type_s[0] = CurType;
				if (CurType == WOLF || CurType == SHEEP || CurType == FOX || CurType == TURTLE || CurType == ANTELOPE) _setTextColor(RED);
				else if (CurType == HUMAN) _setTextColor(YELLOW);
				else _setTextColor(GREEN);
				gotoxy(WORLDINCONSOLE_X + 1 + (i * 2), WORLDINCONSOLE_Y + 1 + j);
				_cputs(type_s);
			};
			_setTextColor(WHITE);
		};
	};
	printWorldBorder({ WORLDINCONSOLE_X,WORLDINCONSOLE_Y }, WorldShift, WORLD_SIZE_N_X, WORLD_SIZE_M_Y);
};

void World::Print(Position WorldShift) {
	system("CLS");
	DrawWorld(WorldShift);
	Commenter();
};

void World::CleanWorld() {
	for (int i = 0; i < WORLD_SIZE_N_X; i++) {
		for (int j = 0; j < WORLD_SIZE_M_Y; j++) {
			VirWorld[i][j] = nullptr;
		}; };
};