#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
#include <stdio.h> 
#include <conio.h>
#include <Windows.h>

#include <algorithm>


/* -------------------------------------------- OTHER ------------------------------------------------- */
/*  ORGANISM NUMBER OF SPECIES  */
#define DEFAULT_NUMBER_OF_ORGANISMS	10 /* NUMBER OF ORGANISMS NOT COUNTING HUMAN */
#define MINUSHUMAN					1	/* NUMBER OF HUMANS */

/* PREVENTION OF INFINITE ITERATION WHILE RANDOMIZING */
#define MAX_NUMBER_OF_ITERATIONS_WHILE_RANDOMAZING	1000 /* Prevents from infinite iteration */

/* THE PRECENTS */
#define THE_FLOOR_OF_SPREAD				10 /* % for a plant to get an offspring (out of 100) */
#define THE_FLOOR_OF_ANTELOPE_ESCAPE	50 /* % for antelope to escape (out of 100) */
#define THE_FLOOR_OF_TURTLE_MOVEMENT	75 /* % for turtle to stay in place (out of 100) */
#define PERCENTOFMAXORGANISM			10 /* % of how many animals will spawn, with 100 % = spawning at all possible spaces  (out of 100) */
#define MULTIPLICATIONTRESHHOLD			50 /* % for animals to get an offspring (out of 100) */

/* THE WORLD IN CONSOLE SIZE VARIABLES */
#define WORLD_SIZE_N_X		10 /* The width of the world */
#define WORLD_SIZE_M_Y		15 /* The heigth of the world */
#define WORLDINCONSOLE_X	45 /* Size of the world in console - x (width) */
#define WORLDINCONSOLE_Y	1 /* Size of the world in console - y (heigth) */

/* MISCELLANEOUS */
#define WORLD_BORDER		"#" /* The printed border of the world */
#define EMPTY_SPACE			" " /* The SPACE printed if no Organisms */
#define NO_TYPE				'+'

/* ---------------------------------------------- TYPES ----------------------------------------------------- */
/*  ANIMALS  */
#define WOLF		'W'
#define SHEEP		'S'
#define FOX			'F'
#define TURTLE		'T'
#define ANTELOPE	'A'

#define HUMAN		'&'

/*  PLANTS  */
#define GRASS		','
#define SOWTHISTLE	'-'
#define	GUARANA		'/'
#define BELLADONNA	']'
#define HOGWEED		'{'

/*  ANIMALS_STR  */
#define WOLF_S		(string)"WOLF"
#define SHEEP_S		(string)"SHEEP"
#define FOX_S		(string)"FOX"
#define TURTLE_S	(string)"TURTLE"
#define ANTELOPE_S	(string)"ANTELOPE"

#define HUMAN_S		(string)"HUMAN"

/*  PLANTS_STR  */
#define GRASS_S			(string)"GRASS"
#define SOWTHISTLE_S	(string)"SOWTHISTLE"
#define	GUARANA_S		(string)"GUARANA"
#define BELLADONNA_S	(string)"BELLADONNA"
#define HOGWEED_S		(string)"HOGWEED"

/*  ----------------------------------------------- CONTROLS --------------------------------------------------- */
#define KEY_UP				0x48 /* walking around the board, by arrows */
#define KEY_DOWN			0x50
#define KEY_LEFT			0x4b
#define KEY_RIGHT			0x4d
#define KEY_ENTER			0x0d /* confirm = enter */
#define KEY_CANCEL			27 /* cancel = esc */
#define KEY_SPECIALABILITY	'h' /* special ability */
#define KEY_Q				'q' /* quit game*/
#define KEY_SAVE			'k' /* save the game = k */
#define KEY_LOAD			'l' /* load the game = l */
#define KEY_W				'w'
#define KEY_A				'a'
#define KEY_S				's'
#define KEY_D				'd'

#define KEY_DELETE		127 /* for writting, delete the character = delete */
#define KEY_BACKSPACE	8 /* for writting, delete the character = backspace */

/* DIRECTIONS */
#define DIR_LEFT	0
#define DIR_RIGHT	1
#define DIR_UP		2
#define DIR_DOWN	3
#define NO_MOVE		-1

/* MOVEMENT */
#define NUMBEROFPOSIBLEMOVES	4
#define DEFAULT_MOVEMENT		1
#define DEFAULT_SPREAD			1
#define ANTELOPE_MOVEMENT		2
#define NOMOVE_NEGATIVEONE		-1
#define NOTFOUND_MINUS1			-1

const int MovementDirections[NUMBEROFPOSIBLEMOVES] = { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

/* -------------------------------------------------- STATS ----------------------------------------------------- */
/* STRENGTH */
#define DEFAULT_STRENGTH		0

#define HUMAN_STRENGTH		5
#define WOLF_STRENGTH		9
#define SHEEP_STRENGTH		4
#define FOX_STRENGTH		3
#define TURTLE_STRENGTH		2
#define ANTELOPE_STRENGTH	4
#define GRASS_STRENGTH		0
#define SOWTHISTLE_STRENGTH	0
#define GUARANA_STRENGTH	0
#define BELLADONNA_STRENGTH	99
#define HOGWEED_STRENGTH	10

/* INITIATIVE */
#define NUMBER_OF_INITIATIVES	7
#define DEFAULT_INITIATIVE		0

#define HUMAN_INITIATIVE	4
#define WOLF_INITIATIVE		5
#define SHEEP_INITIATIVE	4
#define FOX_INITIATIVE		7
#define TURTLE_INITIATIVE	1
#define ANTELOPE_INITIATIVE	4

/* OTHER ANIMAL STATS */
#define TURTLE_DEFENSE					5
#define STRENGTH_INCREASE_GUARANA		3
#define ATTEMPTS_OF_SPREAD_SOWTHISTLE	3
#define HUMAN_NUMBER_OF_TURNS_WITH_ABILITY	5
#define ABILITY_ROUND_DECREASE				1
#define NUMBER_OF_ROUND_UNTIL_POSSIBLE_ACTIVATION_OF_ABILITY	5 /* how many rounds to wait until possible activation of special ability */

/* RESULT OF COLLISION */
#define ORG_LOST							0  /* Organism lost the fight */
#define ORG_WON								1  /* Organism won the fight */
#define ORG_DEFLECTED						2  /* turtle deflected the attack */
#define ORG_MULTIPLICATION					3  /* the organisms are multiplying */
#define ORG_VICTIMTRYESCAPE_WON				4  /* Antelope.collision(Wolf), atelope tries to escape */
#define ORG_VICTIMTRYESCAPE_LOST			5
#define ORG_ATTACKERTRYESCAPE_WON			6  /* other antelope tries e.g. Wolf.collision(Antelope) ??? maybe implement */
#define ORG_ATTACKERTRYESCAPE_LOST			7 