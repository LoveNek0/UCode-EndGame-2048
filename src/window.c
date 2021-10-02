#include "window.h"

void mx_init_ncurses(){
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	timeout(0);
    getmaxyx(stdscr, window.height, window.width);
	mx_init_colors();
	buffer.first = malloc(sizeof(character**) * window.height);
	for(int i = 0; i < window.height; i++){
		buffer.first[i] = malloc(sizeof(character*) * window.width);
		for(int j = 0; j < window.width; j++){
			buffer.first[i][j] = malloc(sizeof(character));
			buffer.first[i][j]->symbol = ' ';
			buffer.first[i][j]->color = 0;
		}
	}
	buffer.second = malloc(sizeof(character**) * window.height);
	for(int i = 0; i < window.height; i++){
		buffer.second[i] = malloc(sizeof(character*) * window.width);
		for(int j = 0; j < window.width; j++){
			buffer.second[i][j] = malloc(sizeof(character));
			buffer.second[i][j]->symbol = ' ';
			buffer.second[i][j]->color = C_BLACK;
		}
	}
}

void mx_mainloop(void (*mainloop)(void)){
	while(true){
		mainloop();
		for(int i = 0; i < window.height; i++)
			for(int j = 0; j < window.width; j++){
				if(
					buffer.first[i][j]->symbol != buffer.second[i][j]->symbol
					||
					buffer.first[i][j]->color != buffer.second[i][j]->color
				)
					mvaddch(i, j, buffer.second[i][j]->symbol | COLOR_PAIR(buffer.second[i][j]->color));
				buffer.first[i][j]->symbol = buffer.second[i][j]->symbol;
				buffer.first[i][j]->color = buffer.second[i][j]->color;
				buffer.second[i][j]->symbol = ' ';
				buffer.second[i][j]->color = C_BLACK;
			}
		refresh();
	}
}

character ***mx_get_buffer(){
	return buffer.second;
}

void mx_exit(int code){
	endwin();
	exit(code);
}

void mx_init_colors(){
	start_color();
    init_pair(C_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(C_RED, COLOR_RED, COLOR_BLACK);
    init_pair(C_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(C_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(C_BLUE, COLOR_BLUE, COLOR_BLACK); 
    init_pair(C_MAGENTA, COLOR_MAGENTA, COLOR_BLACK); 
    init_pair(C_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(C_WHITE, COLOR_WHITE, COLOR_BLACK);
	
	init_pair(B_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(B_RED, COLOR_RED, COLOR_RED);
    init_pair(B_GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(B_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(B_BLUE, COLOR_BLUE, COLOR_BLUE); 
    init_pair(B_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA); 
    init_pair(B_CYAN, COLOR_CYAN, COLOR_CYAN);
	init_pair(B_WHITE, COLOR_WHITE, COLOR_WHITE);
	
	init_pair(BT_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(BT_RED, COLOR_WHITE, COLOR_RED);
    init_pair(BT_GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(BT_YELLOW, COLOR_WHITE, COLOR_YELLOW);
    init_pair(BT_BLUE, COLOR_WHITE, COLOR_BLUE); 
    init_pair(BT_MAGENTA, COLOR_WHITE, COLOR_MAGENTA); 
    init_pair(BT_CYAN, COLOR_WHITE, COLOR_CYAN);
	init_pair(BT_WHITE, COLOR_BLACK, COLOR_WHITE);
	
	init_pair(BT_RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(BT_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(BT_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BT_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK); 
    init_pair(BT_MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK); 
    init_pair(BT_CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(BT_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
}
