#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "mx_lib.h"

/*
STATE
	0 - main menu
	1 - select level
	2 - ingame
	
STATE	MENU
	0
		0 - PLAY
		1 - RECORDS
		2 - ABOUT
		3 - QUIT
		
	1
		0 - 4x4
		1 - 6x6
		2 - 8x8
		
	2
		0 - back
*/

struct s_record{
	int value;
	int steps;
	int max_value;
}	record;

struct s_game{
	int state;
	int menu;
}	game;

struct s_field{
	int size;
	int width;
	int height;
	int **points;
}	field;

enum s_dirrection{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void init_field();
int get_free_count();
int **get_free_list();
void set_rand_point();
bool move_field(int dirrection);
void loadScore();
void saveScore();
