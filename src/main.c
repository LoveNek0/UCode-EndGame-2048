#include "window.h"
#include <time.h>
#include <locale.h>
#include "game.h"
#include "mx_lib.h"

void checkScore(){
	if(record.value > record.max_value){
		record.max_value = record.value;
		saveScore();
	}
}

void mx_draw_window(){
	character ***chars = mx_get_buffer();
	for(int i = 6; i < 10 + field.size * field.width * 2 + 2 + 22; i++){
		chars[4][i]->symbol = '#';
		chars[4][i]->color = B_WHITE;
		chars[3][i]->symbol = '#';
		chars[3][i]->color = B_WHITE;
	}
	for(int i = 6; i < 10 + field.size * field.width * 2 + 2 + 22; i++){
		chars[5 + field.size * field.height][i]->symbol = '#';
		chars[5 + field.size * field.height][i]->color = B_WHITE;
		chars[5 + field.size * field.height + 1][i]->symbol = '#';
		chars[5 + field.size * field.height + 1][i]->color = B_WHITE;
	}
	for(int i = 5; i < 5 + field.size * field.height; i++){
		chars[i][9]->color = B_WHITE;
		chars[i][9]->symbol = '#';
		chars[i][8]->color = B_WHITE;
		chars[i][8]->symbol = '#';
		chars[i][7]->color = B_WHITE;
		chars[i][7]->symbol = '#';
		chars[i][6]->color = B_WHITE;
		chars[i][6]->symbol = '#';
	}
	for(int i = 5; i < 5 + field.size * field.height; i++){
		chars[i][10 + field.size * field.width * 2 + 20]->color = B_WHITE;
		chars[i][10 + field.size * field.width * 2 + 20]->symbol = '#';
		chars[i][10 + field.size * field.width * 2 + 1 + 20]->color = B_WHITE;
		chars[i][10 + field.size * field.width * 2 + 1 + 20]->symbol = '#';
		chars[i][10 + field.size * field.width * 2 + 2 + 20]->color = B_WHITE;
		chars[i][10 + field.size * field.width * 2 + 2 + 20]->symbol = '#';
		chars[i][10 + field.size * field.width * 2 + 3 + 20]->color = B_WHITE;
		chars[i][10 + field.size * field.width * 2 + 3 + 20]->symbol = '#';
	}
}

void mx_draw_game_field(){
	checkScore();
	bool move = false;
	switch(getch()){
		case 'W':
		case 'w':
			move = move_field(UP);
			break;
		case 'S':
		case 's':
			move = move_field(DOWN);
			break;
		case 'A':
		case 'a':
			move = move_field(LEFT);
			break;
		case 'D':
		case 'd':
			move = move_field(RIGHT);
			break;
		case 'Q':
		case 'q':
			game.state = 0;
			break;
	}
	if(get_free_count() == 0)
		game.state = 2;
	character ***chars = mx_get_buffer();
	
	for(int i = 0; i < field.height; i++)
		for(int j = 0; j < field.width; j++){
			int colors[field.size][field.size*2];
			int chs[field.size][field.size*2];
			for(int y = 0; y < field.size; y++)
				for(int x = 0; x < field.size*2; x++){
					colors[y][x] = B_BLACK;
					chs[y][x] = '#';
				}
			if(field.points[i][j] != 0){
				int bg_1 = B_BLACK;
				int bg_2 = B_BLACK;
				int tbg_1 = B_BLACK;
				int tbg_2 = B_BLACK;
				char *value = "";
				switch(field.points[i][j]){
					case 2:
						value = "2";
						bg_1 = B_YELLOW;
						tbg_1 = BT_YELLOW;
						bg_2 = bg_1;
						tbg_2 = tbg_1;
						break;
					case 4:
						value = "4";
						bg_1 = B_GREEN;
						tbg_1 = BT_GREEN;
						bg_2 = bg_1;
						tbg_2 = tbg_1;
						break;
					case 8:
						value = "8";
						bg_1 = B_RED;
						tbg_1 = BT_RED;
						bg_2 = bg_1;
						tbg_2 = tbg_1;
						break;
					case 16:
						value = "16";
						bg_1 = B_BLUE;
						tbg_1 = BT_BLUE;
						bg_2 = bg_1;
						tbg_2 = tbg_1;
						break;
					case 32:
						value = "32";
						bg_1 = B_CYAN;
						tbg_1 = BT_CYAN;
						bg_2 = bg_1;
						tbg_2 = tbg_1;
						break;
					case 64:
						value = "64";
						bg_1 = B_MAGENTA;
						tbg_1 = BT_MAGENTA;
						bg_2 = B_YELLOW;
						tbg_2 = BT_YELLOW;
						break;
					case 128:
						value = "128";
						bg_1 = B_MAGENTA;
						tbg_1 = BT_MAGENTA;
						bg_2 = B_GREEN;
						tbg_2 = BT_GREEN;
						break;
					case 256:
						value = "256";
						bg_1 = B_MAGENTA;
						tbg_1 = BT_MAGENTA;
						bg_2 = B_RED;
						tbg_2 = BT_RED;
						break;
					case 512:
						value = "512";
						bg_1 = B_MAGENTA;
						tbg_1 = BT_MAGENTA;
						bg_2 = B_BLUE;
						tbg_2 = BT_BLUE;
						break;
					case 1024:
						value = "1024";
						bg_1 = B_MAGENTA;
						tbg_1 = BT_MAGENTA;
						bg_2 = B_CYAN;
						tbg_2 = BT_CYAN;
						break;
					case 2048:
						value = "2048";
						bg_1 = B_CYAN;
						tbg_1 = BT_CYAN;
						bg_2 = B_YELLOW;
						tbg_2 = BT_YELLOW;
						break;
					case 4096:
						value = "4096";
						bg_1 = B_CYAN;
						tbg_1 = BT_CYAN;
						bg_2 = B_GREEN;
						tbg_2 = BT_GREEN;
						break;
					case 8192:
						value = "8192";
						bg_1 = B_CYAN;
						tbg_1 = BT_CYAN;
						bg_2 = B_RED;
						tbg_2 = BT_RED;
						break;
					case 16384:
						value = "16384";
						bg_1 = B_CYAN;
						tbg_1 = BT_CYAN;
						bg_2 = B_BLUE;
						tbg_2 = BT_BLUE;
						break;
					case 32768:
						value = "32768";
						bg_1 = B_BLUE;
						tbg_1 = BT_BLUE;
						bg_2 = B_YELLOW;
						tbg_2 = BT_YELLOW;
						break;
				}	
				
				for(int y = 0; y < field.size; y++){
					colors[y][0] = bg_1;
					colors[y][1] = bg_1;
				}
				for(int y = 0; y < field.size; y++){
					colors[y][field.size*2 - 1] = bg_1;
					colors[y][field.size*2 - 2] = bg_1;
				}
				for(int x = 0; x < field.size*2; x++)
					colors[0][x] = bg_1;
				for(int x = 0; x < field.size*2; x++)
					colors[field.size - 1][x] = bg_1;
				for(int y = 1; y < field.size - 1; y++)
					for(int x = 2; x < field.size*2 - 2; x++)
						colors[y][x] = bg_2;
				
				int dd = 0;
				for(char *ss = value; *ss != '\0'; ss++){
					colors[field.size/2][field.size - mx_strlen(value)/2 + dd] = tbg_2;
					chs[field.size/2][field.size - mx_strlen(value)/2 + dd] = *ss;
					dd++;
				}
			}
			
			
			for(int y = 0; y < field.size; y++)
					for(int x = 0; x < field.size*2; x++){
						chars[(5 + i * field.size) + y][(10 + j * field.size*2) + x]->symbol = chs[y][x];
						chars[(5 + i * field.size) + y][(10 + j * field.size*2) + x]->color = colors[y][x];
					}
		}
	
	for(int i = 5; i < 5 + field.size * field.height; i++){
		chars[i][10 + field.size * field.width * 2]->color = B_WHITE;
		chars[i][10 + field.size * field.width * 2]->symbol = '#';
		chars[i][10 + field.size * field.width * 2 + 1]->color = B_WHITE;
		chars[i][10 + field.size * field.width * 2 + 1]->symbol = '#';
	}
	character chRi[24][18];
	for(int i = 0; i < 24; i++)
		for(int j = 0; j < 18; j++){
			chRi[i][j].symbol = '#';
			chRi[i][j].color = B_BLACK;
		}
	// 2
	chRi[1][1].color = B_YELLOW;
	chRi[1][2].color = B_YELLOW;
	chRi[1][3].color = B_YELLOW;
	chRi[1][4].color = B_YELLOW;
	
	chRi[2][4].color = B_YELLOW;
	
	chRi[3][1].color = B_YELLOW;
	chRi[3][2].color = B_YELLOW;
	chRi[3][3].color = B_YELLOW;
	chRi[3][4].color = B_YELLOW;
	
	chRi[4][1].color = B_YELLOW;
	
	chRi[5][1].color = B_YELLOW;
	chRi[5][2].color = B_YELLOW;
	chRi[5][3].color = B_YELLOW;
	chRi[5][4].color = B_YELLOW;
	
	// 0
	chRi[1][5].color = B_BLUE;
	chRi[1][6].color = B_BLUE;
	chRi[1][7].color = B_BLUE;
	chRi[1][8].color = B_BLUE;
	
	chRi[2][5].color = B_BLUE;
	chRi[3][5].color = B_BLUE;
	chRi[4][5].color = B_BLUE;
	
	chRi[5][5].color = B_BLUE;
	chRi[5][6].color = B_BLUE;
	chRi[5][7].color = B_BLUE;
	chRi[5][8].color = B_BLUE;
	
	chRi[2][8].color = B_BLUE;
	chRi[3][8].color = B_BLUE;
	chRi[4][8].color = B_BLUE;
	
	// 4
	chRi[1][9].color = B_MAGENTA;
	chRi[1][12].color = B_MAGENTA;
	
	chRi[2][9].color = B_MAGENTA;
	chRi[2][12].color = B_MAGENTA;
	
	chRi[3][9].color = B_MAGENTA;
	chRi[3][10].color = B_MAGENTA;
	chRi[3][11].color = B_MAGENTA;
	chRi[3][12].color = B_MAGENTA;
	
	chRi[4][12].color = B_MAGENTA;
	chRi[5][12].color = B_MAGENTA;
	
	// 8
	chRi[1][13].color = B_RED;
	chRi[1][14].color = B_RED;
	chRi[1][15].color = B_RED;
	chRi[1][16].color = B_RED;
	
	chRi[2][13].color = B_RED;
	chRi[2][16].color = B_RED;
	
	chRi[3][13].color = B_RED;
	chRi[3][14].color = B_RED;
	chRi[3][15].color = B_RED;
	chRi[3][16].color = B_RED;
	
	chRi[4][13].color = B_RED;
	chRi[4][16].color = B_RED;
	
	chRi[5][13].color = B_RED;
	chRi[5][14].color = B_RED;
	chRi[5][15].color = B_RED;
	chRi[5][16].color = B_RED;
	
	for(int i = 0; i < 18; i++)
		chRi[7][i].color = B_WHITE;
	
	chRi[9][1].symbol = 'S';
	chRi[9][1].color = BT_BLACK;
	chRi[9][2].symbol = 'C';
	chRi[9][2].color = BT_BLACK;
	chRi[9][3].symbol = 'O';
	chRi[9][3].color = BT_BLACK;
	chRi[9][4].symbol = 'R';
	chRi[9][4].color = BT_BLACK;
	chRi[9][5].symbol = 'E';
	chRi[9][5].color = BT_BLACK;
	
	char *scoreS = mx_itoa(record.value);
	int scoreL = mx_strlen(scoreS);
	for(int i = 0; i < scoreL; i++){
		chRi[9][15 - i].color = BT_BLACK;
		chRi[9][15 - i].symbol = scoreS[scoreL - 1 - i];
	}
	
	chRi[11][1].symbol = 'M';
	chRi[11][1].color = BT_BLACK;
	chRi[11][2].symbol = 'A';
	chRi[11][2].color = BT_BLACK;
	chRi[11][3].symbol = 'X';
	chRi[11][3].color = BT_BLACK;
	
	char *max_scoreS = mx_itoa(record.max_value);
	int max_scoreL = mx_strlen(max_scoreS);
	for(int i = 0; i < max_scoreL; i++){
		chRi[11][15 - i].color = BT_BLACK;
		chRi[11][15 - i].symbol = max_scoreS[max_scoreL - 1 - i];
	}
	
	chRi[13][1].symbol = 'S';
	chRi[13][1].color = BT_BLACK;
	chRi[13][2].symbol = 'T';
	chRi[13][2].color = BT_BLACK;
	chRi[13][3].symbol = 'E';
	chRi[13][3].color = BT_BLACK;
	chRi[13][4].symbol = 'P';
	chRi[13][4].color = BT_BLACK;
	chRi[13][5].symbol = 'S';
	chRi[13][5].color = BT_BLACK;
	
	char *stepsS = mx_itoa(record.steps);
	int stepsL = mx_strlen(stepsS);
	for(int i = 0; i < stepsL; i++){
		chRi[13][15 - i].color = BT_BLACK;
		chRi[13][15 - i].symbol = stepsS[stepsL - 1 - i];
	}
	
	for(int i = 0; i < 18; i++)
		chRi[15][i].color = B_WHITE;
	
	chRi[17][1].symbol = 'W';
	chRi[17][1].color = BT_YELLOW;
	chRi[17][3].symbol = '-';
	chRi[17][3].color = BT_YELLOW_BLACK;
	chRi[17][5].symbol = 'U';
	chRi[17][5].color = BT_YELLOW_BLACK;
	chRi[17][6].symbol = 'p';
	chRi[17][6].color = BT_YELLOW_BLACK;
	
	chRi[18][1].symbol = 'S';
	chRi[18][1].color = BT_GREEN;
	chRi[18][3].symbol = '-';
	chRi[18][3].color = BT_GREEN_BLACK;
	chRi[18][5].symbol = 'D';
	chRi[18][5].color = BT_GREEN_BLACK;
	chRi[18][6].symbol = 'o';
	chRi[18][6].color = BT_GREEN_BLACK;
	chRi[18][7].symbol = 'w';
	chRi[18][7].color = BT_GREEN_BLACK;
	chRi[18][8].symbol = 'n';
	chRi[18][8].color = BT_GREEN_BLACK;
	
	chRi[19][1].symbol = 'A';
	chRi[19][1].color = BT_BLUE;
	chRi[19][3].symbol = '-';
	chRi[19][3].color = BT_BLUE_BLACK;
	chRi[19][5].symbol = 'L';
	chRi[19][5].color = BT_BLUE_BLACK;
	chRi[19][6].symbol = 'e';
	chRi[19][6].color = BT_BLUE_BLACK;
	chRi[19][7].symbol = 'f';
	chRi[19][7].color = BT_BLUE_BLACK;
	chRi[19][8].symbol = 't';
	chRi[19][8].color = BT_BLUE_BLACK;
	
	chRi[20][1].symbol = 'D';
	chRi[20][1].color = BT_MAGENTA;
	chRi[20][3].symbol = '-';
	chRi[20][3].color = BT_MAGENTA_BLACK;
	chRi[20][5].symbol = 'R';
	chRi[20][5].color = BT_MAGENTA_BLACK;
	chRi[20][6].symbol = 'i';
	chRi[20][6].color = BT_MAGENTA_BLACK;
	chRi[20][7].symbol = 'g';
	chRi[20][7].color = BT_MAGENTA_BLACK;
	chRi[20][8].symbol = 'h';
	chRi[20][8].color = BT_MAGENTA_BLACK;
	chRi[20][9].symbol = 't';
	chRi[20][9].color = BT_MAGENTA_BLACK;
	
	chRi[22][1].symbol = 'Q';
	chRi[22][1].color = BT_RED;
	chRi[22][2].symbol = 'u';
	chRi[22][2].color = BT_RED_BLACK;
	chRi[22][3].symbol = 'i';
	chRi[22][3].color = BT_RED_BLACK;
	chRi[22][4].symbol = 't';
	chRi[22][4].color = BT_RED_BLACK;
	
	int y = 0;
	int x = 0;
	for(int i = 5; i < 29; i++){
		x = 0;
		for(int j = 10 + field.size * field.width * 2 + 2; j < 10 + field.size * field.width * 2 + 2 + 18; j++){
			chars[i][j]->symbol = chRi[y][x].symbol;
			chars[i][j]->color = chRi[y][x].color;
			x++;
		}
		y++;
	}
}

void mx_draw_mainmenu(){
	switch(getch()){
		case 'W':
		case 'w':
			game.menu--;
		break;
		case 'S':
		case 's':
			game.menu++;
		break;
		case ' ':
		case '\n':
			if(game.menu == 1)
				mx_exit(0);
			else{
				game.menu = 0;
				game.state = 1;
				init_field(4,4);
				set_rand_point();
				set_rand_point();
			}
		break;
	}
	if(game.menu > 1)
		game.menu = 0;
	if(game.menu < 0)
		game.menu = 1;
	
	character ***chars = mx_get_buffer();
	character ch[24][68];
	for(int i = 0; i < 24; i++)
		for(int j = 0; j < 68; j++){
			ch[i][j].symbol = '#';
			ch[i][j].color = B_BLACK;
		}
	
	int px = 20;
	int py = 5;
	
	// P
	ch[py][px].color = B_BLUE;
	ch[py][px+1].color = B_BLUE;
	ch[py + 1][px].color = B_BLUE;
	ch[py + 1][px+1].color = B_BLUE;
	ch[py + 2][px].color = B_BLUE;
	ch[py + 2][px+1].color = B_BLUE;
	ch[py + 3][px].color = B_BLUE;
	ch[py + 3][px+1].color = B_BLUE;
	ch[py + 4][px].color = B_BLUE;
	ch[py + 4][px+1].color = B_BLUE;
	
	ch[py][px + 2].color = B_BLUE;
	ch[py][px + 3].color = B_BLUE;
	ch[py][px + 4].color = B_BLUE;
	ch[py][px + 5].color = B_BLUE;
	
	ch[py + 1][px + 4].color = B_BLUE;
	ch[py + 1][px + 5].color = B_BLUE;
	ch[py + 2][px + 4].color = B_BLUE;
	ch[py + 2][px + 5].color = B_BLUE;
	
	ch[py + 2][px + 1].color = B_BLUE;
	ch[py + 2][px + 2].color = B_BLUE;
	ch[py + 2][px + 3].color = B_BLUE;
	ch[py + 2][px + 4].color = B_BLUE;
	
	// L
	ch[py][px + 7].color = B_BLUE;
	ch[py][px + 8].color = B_BLUE;
	ch[py + 1][px + 7].color = B_BLUE;
	ch[py + 1][px + 8].color = B_BLUE;
	ch[py + 2][px + 7].color = B_BLUE;
	ch[py + 2][px + 8].color = B_BLUE;
	ch[py + 3][px + 7].color = B_BLUE;
	ch[py + 3][px + 8].color = B_BLUE;
	ch[py + 4][px + 7].color = B_BLUE;
	ch[py + 4][px + 8].color = B_BLUE;
	
	ch[py + 4][px + 9].color = B_BLUE;
	ch[py + 4][px + 10].color = B_BLUE;
	ch[py + 4][px + 11].color = B_BLUE;
	ch[py + 4][px + 12].color = B_BLUE;
	
	// A
	ch[py][px + 16].color = B_BLUE;
	ch[py][px + 17].color = B_BLUE;
	
	ch[py + 2][px + 16].color = B_BLUE;
	ch[py + 2][px + 17].color = B_BLUE;
	
	ch[py + 1][px + 14].color = B_BLUE;
	ch[py + 1][px + 15].color = B_BLUE;
	ch[py + 2][px + 14].color = B_BLUE;
	ch[py + 2][px + 15].color = B_BLUE;
	ch[py + 3][px + 14].color = B_BLUE;
	ch[py + 3][px + 15].color = B_BLUE;
	ch[py + 4][px + 14].color = B_BLUE;
	ch[py + 4][px + 15].color = B_BLUE;
	
	ch[py + 1][px + 18].color = B_BLUE;
	ch[py + 1][px + 19].color = B_BLUE;
	ch[py + 2][px + 18].color = B_BLUE;
	ch[py + 2][px + 19].color = B_BLUE;
	ch[py + 3][px + 18].color = B_BLUE;
	ch[py + 3][px + 19].color = B_BLUE;
	ch[py + 4][px + 18].color = B_BLUE;
	ch[py + 4][px + 19].color = B_BLUE;
	
	// Y
	ch[py][px + 21].color = B_BLUE;
	ch[py][px + 22].color = B_BLUE;
	ch[py + 1][px + 21].color = B_BLUE;
	ch[py + 1][px + 22].color = B_BLUE;
	
	
	ch[py + 2][px + 23].color = B_BLUE;
	ch[py + 2][px + 24].color = B_BLUE;
	
	ch[py][px + 25].color = B_BLUE;
	ch[py][px + 26].color = B_BLUE;
	ch[py + 1][px + 25].color = B_BLUE;
	ch[py + 1][px + 26].color = B_BLUE;
	ch[py + 2][px + 25].color = B_BLUE;
	ch[py + 2][px + 26].color = B_BLUE;
	ch[py + 3][px + 25].color = B_BLUE;
	ch[py + 3][px + 26].color = B_BLUE;
	
	ch[py + 4][px + 22].color = B_BLUE;
	ch[py + 4][px + 23].color = B_BLUE;
	ch[py + 4][px + 24].color = B_BLUE;
	
	int qx = px;
	int qy = py + 2 + 5;
	
	// Q
	ch[qy][qx + 2].color = B_RED;
	ch[qy][qx + 3].color = B_RED;
	
	ch[qy + 1][qx].color = B_RED;
	ch[qy + 1][qx+1].color = B_RED;
	ch[qy + 2][qx].color = B_RED;
	ch[qy + 2][qx+1].color = B_RED;
	
	ch[qy + 1][qx + 4].color = B_RED;
	ch[qy + 1][qx + 5].color = B_RED;
	ch[qy + 2][qx + 4].color = B_RED;
	ch[qy + 2][qx + 5].color = B_RED;
	
	ch[qy + 3][qx + 2].color = B_RED;
	ch[qy + 3][qx + 3].color = B_RED;
	
	ch[qy + 4][qx + 4].color = B_RED;
	ch[qy + 4][qx + 5].color = B_RED;
	
	// U
	ch[qy][qx + 7].color = B_RED;
	ch[qy][qx + 8].color = B_RED;
	ch[qy + 1][qx + 7].color = B_RED;
	ch[qy + 1][qx + 8].color = B_RED;
	ch[qy + 2][qx + 7].color = B_RED;
	ch[qy + 2][qx + 8].color = B_RED;
	ch[qy + 3][qx + 7].color = B_RED;
	ch[qy + 3][qx + 8].color = B_RED;

	ch[qy][qx + 11].color = B_RED;
	ch[qy][qx + 12].color = B_RED;
	ch[qy + 1][qx + 11].color = B_RED;
	ch[qy + 1][qx + 12].color = B_RED;
	ch[qy + 2][qx + 11].color = B_RED;
	ch[qy + 2][qx + 12].color = B_RED;
	ch[qy + 3][qx + 11].color = B_RED;
	ch[qy + 3][qx + 12].color = B_RED;
	
	ch[qy + 4][qx + 9].color = B_RED;
	ch[qy + 4][qx + 10].color = B_RED;
	
	// I
	ch[qy][qx + 16].color = B_RED;
	ch[qy][qx + 17].color = B_RED;
	ch[qy + 2][qx + 16].color = B_RED;
	ch[qy + 2][qx + 17].color = B_RED;
	ch[qy + 3][qx + 16].color = B_RED;
	ch[qy + 3][qx + 17].color = B_RED;
	ch[qy + 4][qx + 16].color = B_RED;
	ch[qy + 4][qx + 17].color = B_RED;
	
	// T
	ch[qy][qx + 21].color = B_RED;
	ch[qy][qx + 22].color = B_RED;
	ch[qy][qx + 23].color = B_RED;
	ch[qy][qx + 24].color = B_RED;
	ch[qy][qx + 25].color = B_RED;
	ch[qy][qx + 26].color = B_RED;
	
	ch[qy + 1][qx + 23].color = B_RED;
	ch[qy + 1][qx + 24].color = B_RED;
	ch[qy + 2][qx + 23].color = B_RED;
	ch[qy + 2][qx + 24].color = B_RED;
	ch[qy + 3][qx + 23].color = B_RED;
	ch[qy + 3][qx + 24].color = B_RED;
	ch[qy + 4][qx + 23].color = B_RED;
	ch[qy + 4][qx + 24].color = B_RED;
	
	int sx = px - 8;
	int sy = 0;
	
	if(game.menu == 0)
		sy = py;
	else
		sy = qy;
	
	ch[sy + 2][sx + 4].color = B_YELLOW;
	ch[sy + 2][sx + 5].color = B_YELLOW;
	
	ch[sy + 1][sx + 2].color = B_YELLOW;
	ch[sy + 1][sx + 3].color = B_YELLOW;
	ch[sy + 3][sx + 2].color = B_YELLOW;
	ch[sy + 3][sx + 3].color = B_YELLOW;
	
	ch[sy][sx + 0].color = B_YELLOW;
	ch[sy][sx + 1].color = B_YELLOW;
	ch[sy + 4][sx + 0].color = B_YELLOW;
	ch[sy + 4][sx + 1].color = B_YELLOW;
	
	ch[20][50].symbol = 'W';
	ch[20][50].color = BT_YELLOW;
	ch[20][52].symbol = '-';
	ch[20][52].color = BT_YELLOW_BLACK;
	ch[20][54].symbol = 'U';
	ch[20][54].color = BT_YELLOW_BLACK;
	ch[20][55].symbol = 'p';
	ch[20][55].color = BT_YELLOW_BLACK;
	
	ch[21][50].symbol = 'S';
	ch[21][50].color = BT_GREEN;
	ch[21][52].symbol = '-';
	ch[21][52].color = BT_GREEN_BLACK;
	ch[21][54].symbol = 'D';
	ch[21][54].color = BT_GREEN_BLACK;
	ch[21][55].symbol = 'o';
	ch[21][55].color = BT_GREEN_BLACK;
	ch[21][56].symbol = 'w';
	ch[21][56].color = BT_GREEN_BLACK;
	ch[21][57].symbol = 'n';
	ch[21][57].color = BT_GREEN_BLACK;
	
	ch[22][50].symbol = 'S';
	ch[22][50].color = BT_MAGENTA;
	ch[22][51].symbol = 'P';
	ch[22][51].color = BT_MAGENTA;
	ch[22][52].symbol = 'A';
	ch[22][52].color = BT_MAGENTA;
	ch[22][53].symbol = 'C';
	ch[22][53].color = BT_MAGENTA;
	ch[22][54].symbol = 'E';
	ch[22][54].color = BT_MAGENTA;
	ch[22][56].symbol = '-';
	ch[22][56].color = BT_MAGENTA_BLACK;
	ch[22][58].symbol = 'S';
	ch[22][58].color = BT_MAGENTA_BLACK;
	ch[22][59].symbol = 'e';
	ch[22][59].color = BT_MAGENTA_BLACK;
	ch[22][60].symbol = 'l';
	ch[22][60].color = BT_MAGENTA_BLACK;
	ch[22][61].symbol = 'e';
	ch[22][61].color = BT_MAGENTA_BLACK;
	ch[22][62].symbol = 'c';
	ch[22][62].color = BT_MAGENTA_BLACK;
	ch[22][63].symbol = 't';
	ch[22][63].color = BT_MAGENTA_BLACK;
	
	for(int i = 0; i < 24; i++)
		for(int j = 0; j < 68; j++){
			chars[5 + i][10 + j]->symbol = ch[i][j].symbol;
			chars[5 + i][10 + j]->color = ch[i][j].color;
		}
}

void mx_draw_end(){
	if(getch()==' ')
		game.state=0;
	character ***chars = mx_get_buffer();
	character ch[24][68];
	for(int i = 0; i < 24; i++)
		for(int j = 0; j < 68; j++){
			ch[i][j].symbol = '#';
			ch[i][j].color = B_BLACK;
		}
		
	int ex = 24;
	int ey = 5;
	
	// E
	ch[ey][ex].color = B_RED;
	ch[ey][ex + 1].color = B_RED;
	ch[ey + 1][ex].color = B_RED;
	ch[ey + 1][ex + 1].color = B_RED;
	ch[ey + 2][ex].color = B_RED;
	ch[ey + 2][ex + 1].color = B_RED;
	ch[ey + 3][ex].color = B_RED;
	ch[ey + 3][ex + 1].color = B_RED;
	ch[ey + 4][ex].color = B_RED;
	ch[ey + 4][ex + 1].color = B_RED;
	
	ch[ey][ex + 2].color = B_RED;
	ch[ey][ex + 3].color = B_RED;
	ch[ey][ex + 4].color = B_RED;
	ch[ey][ex + 5].color = B_RED;
	
	ch[ey + 2][ex + 2].color = B_RED;
	ch[ey + 2][ex + 3].color = B_RED;
	ch[ey + 2][ex + 4].color = B_RED;
	ch[ey + 2][ex + 5].color = B_RED;
	
	ch[ey + 4][ex + 2].color = B_RED;
	ch[ey + 4][ex + 3].color = B_RED;
	ch[ey + 4][ex + 4].color = B_RED;
	ch[ey + 4][ex + 5].color = B_RED;
	
	// N
	ch[ey][ex + 7].color = B_RED;
	ch[ey][ex + 8].color = B_RED;
	ch[ey + 1][ex + 7].color = B_RED;
	ch[ey + 1][ex + 8].color = B_RED;
	ch[ey + 2][ex + 7].color = B_RED;
	ch[ey + 2][ex + 8].color = B_RED;
	ch[ey + 3][ex + 7].color = B_RED;
	ch[ey + 3][ex + 8].color = B_RED;
	ch[ey + 4][ex + 7].color = B_RED;
	ch[ey + 4][ex + 8].color = B_RED;
	
	ch[ey + 1][ex + 9].color = B_RED;
	ch[ey + 2][ex + 10].color = B_RED;
	
	ch[ey][ex + 11].color = B_RED;
	ch[ey][ex + 12].color = B_RED;
	ch[ey + 1][ex + 11].color = B_RED;
	ch[ey + 1][ex + 12].color = B_RED;
	ch[ey + 2][ex + 11].color = B_RED;
	ch[ey + 2][ex + 12].color = B_RED;
	ch[ey + 3][ex + 11].color = B_RED;
	ch[ey + 3][ex + 12].color = B_RED;
	ch[ey + 4][ex + 11].color = B_RED;
	ch[ey + 4][ex + 12].color = B_RED;
	
	// D
	ch[ey][ex + 14].color = B_RED;
	ch[ey][ex + 15].color = B_RED;
	ch[ey + 1][ex + 14].color = B_RED;
	ch[ey + 1][ex + 15].color = B_RED;
	ch[ey + 2][ex + 14].color = B_RED;
	ch[ey + 2][ex + 15].color = B_RED;
	ch[ey + 3][ex + 14].color = B_RED;
	ch[ey + 3][ex + 15].color = B_RED;
	ch[ey + 4][ex + 14].color = B_RED;
	ch[ey + 4][ex + 15].color = B_RED;
	
	ch[ey][ex + 16].color = B_RED;
	ch[ey][ex + 17].color = B_RED;
	ch[ey + 4][ex + 16].color = B_RED;
	ch[ey + 4][ex + 17].color = B_RED;
	
	ch[ey + 1][ex + 18].color = B_RED;
	ch[ey + 2][ex + 19].color = B_RED;
	ch[ey + 3][ex + 18].color = B_RED;
	
	ex--;
	ch[11][1 + ex].symbol = 'S';
	ch[11][1 + ex].color = BT_BLACK;
	ch[11][2 + ex].symbol = 'C';
	ch[11][2 + ex].color = BT_BLACK;
	ch[11][3 + ex].symbol = 'O';
	ch[11][3 + ex].color = BT_BLACK;
	ch[11][4 + ex].symbol = 'R';
	ch[11][4 + ex].color = BT_BLACK;
	ch[11][5 + ex].symbol = 'E';
	ch[11][5 + ex].color = BT_BLACK;
	
	char *scoreS = mx_itoa(record.value);
	int scoreL = mx_strlen(scoreS);
	for(int i = 0; i < scoreL; i++){
		ch[11][20 - i  + ex].color = BT_BLACK;
		ch[11][20 - i  + ex].symbol = scoreS[scoreL - 1 - i];
	}
	
	ch[12][1 + ex].symbol = 'S';
	ch[12][1 + ex].color = BT_BLACK;
	ch[12][2 + ex].symbol = 'T';
	ch[12][2 + ex].color = BT_BLACK;
	ch[12][3 + ex].symbol = 'E';
	ch[12][3 + ex].color = BT_BLACK;
	ch[12][4 + ex].symbol = 'P';
	ch[12][4 + ex].color = BT_BLACK;
	ch[12][5 + ex].symbol = 'S';
	ch[12][5 + ex].color = BT_BLACK;
	
	scoreS = mx_itoa(record.steps);
	scoreL = mx_strlen(scoreS);
	for(int i = 0; i < scoreL; i++){
		ch[12][20 - i  + ex].color = BT_BLACK;
		ch[12][20 - i  + ex].symbol = scoreS[scoreL - 1 - i];
	}
	
	ch[14][1 + ex].symbol = 'M';
	ch[14][1 + ex].color = BT_BLACK;
	ch[14][2 + ex].symbol = 'A';
	ch[14][2 + ex].color = BT_BLACK;
	ch[14][3 + ex].symbol = 'X';
	ch[14][3 + ex].color = BT_BLACK;
	ch[14][5 + ex].symbol = 'S';
	ch[14][5 + ex].color = BT_BLACK;
	ch[14][6 + ex].symbol = 'C';
	ch[14][6 + ex].color = BT_BLACK;
	ch[14][7 + ex].symbol = 'O';
	ch[14][7 + ex].color = BT_BLACK;
	ch[14][8 + ex].symbol = 'R';
	ch[14][8 + ex].color = BT_BLACK;
	ch[14][9 + ex].symbol = 'E';
	ch[14][9 + ex].color = BT_BLACK;
	
	scoreS = mx_itoa(record.max_value);
	scoreL = mx_strlen(scoreS);
	for(int i = 0; i < scoreL; i++){
		ch[14][20 - i  + ex].color = BT_BLACK;
		ch[14][20 - i  + ex].symbol = scoreS[scoreL - 1 - i];
	}
	
	scoreS = "Press SPACE to return";
	scoreL = mx_strlen(scoreS);
	for(int i = 0; i < scoreL; i++){
		ch[17][20 - i  + ex].color = BT_BLACK;
		ch[17][20 - i  + ex].symbol = scoreS[scoreL - 1 - i];
	}
	
	for(int i = 0; i < 24; i++)
		for(int j = 0; j < 68; j++){
			chars[5 + i][10 + j]->symbol = ch[i][j].symbol;
			chars[5 + i][10 + j]->color = ch[i][j].color;
		}
}

void onDisplay(){
	switch(game.state){
		case 0:
		mx_draw_mainmenu();
		break;
		case 1:
		mx_draw_game_field();
		break;
		case 2:
		mx_draw_end();
		break;
	}
	mx_draw_window();
}

int main(){
	setlocale(LC_ALL, "");
	srand ( time(NULL) );
	mx_init_ncurses();
	if(window.width < 82 || window.height < 32){
		endwin();
		printf("error: console size must be more then 82x32\n");
		exit(0);
	}
	init_field(4,4);
	game.state = 0;
	mx_mainloop(onDisplay);
	return 0;
}
