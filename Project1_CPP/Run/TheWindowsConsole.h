#pragma once
#include "TheProjectConstants.h"

/* ------------------------------------- CURSOR --------------------------------------- */
#define NOCURSOR		0
#define NORMALCURSOR	1
#define SOLIDCURSOR		2


/* -------------------------------------- COLOR --------------------------------------- */
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15


/* Position class - 2D - x and y variables */
class Position {
public:
	int x, y;
	Position() : x(0), y(0) {};
	Position(int new_x, int new_y) : x(new_x), y(new_y) {};
	Position(const Position& otherPos) {
		x = otherPos.x;	y = otherPos.y;
	};
	Position(Position&& otherPos) noexcept {
		x = otherPos.x;	y = otherPos.y;
	};
	Position& operator=(const Position& otherPos) noexcept {
		x = otherPos.x;	y = otherPos.y;
		return *this;
	};
	Position& operator=(Position&& otherPos) noexcept {
		x = otherPos.x;	y = otherPos.y;
		return *this;
	};
	void Change_Position(int new_x, int new_y) {
		x = new_x;	y = new_y;
	};
	~Position() {};
};

vector<string> getAllFilesWithinFolder()
{
	vector<string> NamesOfFiles;
	char current_directory[MAX_PATH];
	if (::GetCurrentDirectoryA(MAX_PATH, current_directory) != 0)
	{
		string search_path = string(current_directory) + "\\*.txt";
		WIN32_FIND_DATAW fd;
		HANDLE hFind = ::FindFirstFileW(wstring(search_path.begin(), search_path.end()).c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					wstring ws(fd.cFileName);
					string filename(ws.begin(), ws.end());
					NamesOfFiles.push_back(filename);
				}
			} while (::FindNextFileW(hFind, &fd));
			::FindClose(hFind);
		}
	}
	return NamesOfFiles;
};

/* GO TO XY */
void gotoxy(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(consoleHandle, pos);
};

/* COLOR OF TEXT IN CONSOLE */
void _setTextColor(int newcolor) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, newcolor);
};

/* SET CURSOR TO INVISIBLE OR VISIBLE */
void _setCursor(int CursorType) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info = { 1, TRUE };
	switch (CursorType) {
	case NOCURSOR:
		info.bVisible = FALSE;
		break;
	case NORMALCURSOR:
		info.bVisible = TRUE;
		info.dwSize = 13;
		break;
	case SOLIDCURSOR:
		info.bVisible = TRUE;
		info.dwSize = 100;
		break;
	};
	SetConsoleCursorInfo(consoleHandle, &info);
};

/* GET SIZE OF CONSOLE SCREEN */
Position getSizeOfScreen()
{
	Position screenSize = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	screenSize.x = static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	screenSize.y = static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	return screenSize;
};

#define THEADDITIONAL_PLACE_FOR_A_ROW		2
#define THEADDITIONAL_PLACE_FOR_A_COLUMN	1

/* PRINT WORLD BORDER - N (x) x M (y) : world size, thePositionOnScreen - the position on console  */
/* start - the starting position in the world that will printed */
void printWorldBorder(Position thePositionOnScreen, Position start, int size_N, int size_M) {
	Position screenSize = getSizeOfScreen(); /* The size of console window */
	int numberOfRows = size_M + THEADDITIONAL_PLACE_FOR_A_ROW, numberOfColumns = (size_N * 2) + THEADDITIONAL_PLACE_FOR_A_COLUMN; /* *2 because it's more pleasing looking */
	if (numberOfColumns > (screenSize.x - thePositionOnScreen.x)) numberOfColumns = screenSize.x - thePositionOnScreen.x;
	if (numberOfRows > (screenSize.y - thePositionOnScreen.y)) numberOfRows = screenSize.y - thePositionOnScreen.y;

	for (int j = 0; j < numberOfRows; j++) {
		if (start.x == 0) { gotoxy(thePositionOnScreen.x, thePositionOnScreen.y + j);   _cputs(WORLD_BORDER); };
		if ((thePositionOnScreen.x + (size_N * 2) - start.x) <= screenSize.x)
		{
			if ((thePositionOnScreen.x + (size_N * 2)) < screenSize.x) { gotoxy(thePositionOnScreen.x + (size_N * 2), thePositionOnScreen.y + j); _cputs(WORLD_BORDER); }
			else { gotoxy(screenSize.x, thePositionOnScreen.y + j); _cputs(WORLD_BORDER); };
		};
	};
	for (int i = 0; i < numberOfColumns; i++) {
		if (start.y == 0) { gotoxy(thePositionOnScreen.x + i, thePositionOnScreen.y);  _cputs(WORLD_BORDER); };
		if ((thePositionOnScreen.y + size_M + 1 - start.y) <= screenSize.y) {
			if ((thePositionOnScreen.y + size_M + 1) < screenSize.y) { gotoxy(thePositionOnScreen.x + i, thePositionOnScreen.y + size_M + 1); _cputs(WORLD_BORDER); }
			else { gotoxy(thePositionOnScreen.x + i, screenSize.y); _cputs(WORLD_BORDER); };
		};
	};
};

/* Bubble Sort - results in decreasing list */
void swap(int* FirstNumber, int* SecondNumber) {
	int temp = *FirstNumber;
	*FirstNumber = *SecondNumber;
	*SecondNumber = temp;
};

/* Bubble Sort - results in decreasing list */
void BubbleSort(int Array[], int NumberOfElements) {
	for (int i = 0; i < NumberOfElements - 1; i++)
		for (int j = 0; j < NumberOfElements - i - 1; j++)
			if (Array[j] < Array[j + 1])
				swap(&Array[j], &Array[j + 1]);
};