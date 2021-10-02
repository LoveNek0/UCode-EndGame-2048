#pragma once

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum character_color{
	C_BLACK,
	C_RED,
	C_GREEN,
	C_YELLOW,
	C_BLUE,
	C_MAGENTA,
	C_CYAN,
	C_WHITE,
	
	B_BLACK,
	B_RED,
	B_GREEN,
	B_YELLOW,
	B_BLUE,
	B_MAGENTA,
	B_CYAN,
	B_WHITE,
	
	BT_BLACK,
	BT_RED,
	BT_GREEN,
	BT_YELLOW,
	BT_BLUE,
	BT_MAGENTA,
	BT_CYAN,
	BT_WHITE,
	
	BT_RED_BLACK,
	BT_GREEN_BLACK,
	BT_YELLOW_BLACK,
	BT_BLUE_BLACK,
	BT_MAGENTA_BLACK,
	BT_CYAN_BLACK,
	BT_WHITE_BLACK
};

typedef
struct s_character{
	int symbol;
	int color;
}	character;

struct s_window{
	int width;
	int height;
}	window;

struct s_buffer{
	character ***first;
	character ***second;
}	buffer;

void mx_init_ncurses();
void mx_mainloop(void (*mainloop)(void));
character ***mx_get_buffer();
void mx_exit(int code);
void mx_init_colors();
