#include "World.h"

void theProgram(World* VirtualWorld) {
	_setCursor(NOCURSOR);
	Position ScreenSize = getSizeOfScreen();
	int zn = 0;
	Position WorldShift = { 0,0 };
	while (zn != KEY_Q) {
		zn = _getch();
		switch (zn) {
		case KEY_W:
			if (WorldShift.y > 0) {
				WorldShift.y--;
				VirtualWorld->Print(WorldShift);
			};
			break;
		case KEY_A:
			if (WorldShift.x > 0) {
				WorldShift.x--;
				VirtualWorld->Print(WorldShift);
			};
			break;
		case KEY_S:
			if (WorldShift.y < WORLD_SIZE_M_Y - (ScreenSize.y - WORLDINCONSOLE_Y - 1)) {
				WorldShift.y++;
				VirtualWorld->Print(WorldShift);
			};
			break;
		case KEY_D:
			if (WorldShift.x < WORLD_SIZE_N_X  - (ScreenSize.x - WORLDINCONSOLE_X - 1)) {
				WorldShift.x++;
				VirtualWorld->Print(WorldShift);
			};
			break;
		case KEY_UP:
			VirtualWorld->NextStep(DIR_UP);
			VirtualWorld->Print(WorldShift);
			break;
		case KEY_DOWN:
			VirtualWorld->NextStep(DIR_DOWN);
			VirtualWorld->Print(WorldShift);
			break;
		case KEY_LEFT:
			VirtualWorld->NextStep(DIR_LEFT);
			VirtualWorld->Print(WorldShift);
			break;
		case KEY_RIGHT:
			VirtualWorld->NextStep(DIR_RIGHT);
			VirtualWorld->Print(WorldShift);
			break;
		case KEY_SPECIALABILITY:
			VirtualWorld->TurnOnSuperPower();
			break;
		case KEY_ENTER:
			VirtualWorld->NextStep(NO_MOVE);
			VirtualWorld->Print(WorldShift);
			break;
		case KEY_SAVE:
			VirtualWorld->SaveFile();
			VirtualWorld->Print(WorldShift);
			break;
		case KEY_LOAD:
			VirtualWorld->LoadFile();
			VirtualWorld->Print(WorldShift);
			break;
		default:
			break;
		};
	};
};

int main() {
	World VirtualWorld;
	srand(time(NULL));
	VirtualWorld.InitializeOrganisms();
	VirtualWorld.Print({ 0,0 });
	theProgram(&VirtualWorld);
	return 0;
};