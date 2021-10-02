#include "game.h"

void init_field(int w, int h){
	record.value = 0;
	record.steps = 0;
	field.width = w;
	field.height = h;
	if(w == 8)
		field.size = 3;
	if(w == 6)
		field.size = 4;
	if(w == 4)
		field.size = 6;
	field.points = malloc(sizeof(int *) * field.height);
	for(int i = 0; i < field.height; i++){
		field.points[i] = malloc(sizeof(int) * field.width);
		for(int j = 0; j < field.width; j++)
			field.points[i][j] = 0;
	}
	loadScore();
}

int get_free_count(){
	int c = 0;
	for(int i = 0; i < field.height; i++)
		for(int j = 0; j < field.width; j++)
			if(field.points[i][j] == 0)
				c++;
	return c;
}

int **get_free_list(){
	int **list = malloc(sizeof(int*) * get_free_count());
	int d = 0;
	for(int i = 0; i < field.height; i++)
		for(int j = 0; j < field.width; j++)
			if(field.points[i][j] == 0)
				list[d++] = &field.points[i][j];
	return list;
}

void set_rand_point(){
	int count = get_free_count();
	if(count > 0){
		int **frees = get_free_list();
		*(frees[rand() % count]) = 2;
	}
}

bool sort_up(){
	bool result = false;
	for(int i = 0; i < field.width; i++){
		bool end = false;
		while(!end){
			end = true;
			for(int j = 0; j < field.height - 1; j++)
				if(field.points[j][i] == 0 && field.points[j + 1][i] != 0){
					end = false;
					field.points[j][i] = field.points[j + 1][i];
					field.points[j + 1][i] = 0;
					result = true;
				}
		}
	}
	return result;
}
bool sort_down(){
	bool result = false;
	for(int i = 0; i < field.width; i++){
		bool end = false;
		while(!end){
			end = true;
			for(int j = field.height - 1; j > 0; j--)
				if(field.points[j][i] == 0 && field.points[j - 1][i] != 0){
					end = false;
					field.points[j][i] = field.points[j - 1][i];
					field.points[j - 1][i] = 0;
					result = true;
				}
		}
	}
	return result;
}
bool sort_left(){
	bool result = false;
	for(int i = 0; i < field.height; i++){
		bool end = false;
		while(!end){
			end = true;
			for(int j = 0; j < field.width - 1; j++)
				if(field.points[i][j] == 0 && field.points[i][j + 1] != 0){
					end = false;
					field.points[i][j] = field.points[i][j + 1];
					field.points[i][j + 1] = 0;
					result = true;
				}
		}
	}
	return result;
}
bool sort_right(){
	bool result = false;
	for(int i = 0; i < field.height; i++){
		bool end = false;
		while(!end){
			end = true;
			for(int j = field.width - 1; j > 0; j--)
				if(field.points[i][j] == 0 && field.points[i][j - 1] != 0){
					end = false;
					field.points[i][j] = field.points[i][j - 1];
					field.points[i][j - 1] = 0;
					result = true;
				}
		}
	}
	return result;
}

bool move_up(){
	bool result = false;
	for(int i = 0; i < field.width; i++){
		for(int j = field.height - 1; j > 0; j--)
			if(
				field.points[j][i] != 0
				&&
				field.points[j - 1][i] == field.points[j][i]
			){
				field.points[j][i] = 0;
				field.points[j - 1][i] *= 2;
				record.value += field.points[j - 1][i];
				j--;
			}
	}
	return result;
}
bool move_down(){
	bool result = false;
	for(int i = 0; i < field.width; i++){
		for(int j = 0; j < field.height - 1; j++)
			if(
				field.points[j][i] != 0
				&&
				field.points[j + 1][i] == field.points[j][i]
			){
				field.points[j][i] = 0;
				field.points[j + 1][i] *= 2;
				record.value += field.points[j + 1][i];
				j++;
			}
	}
	return result;
}
bool move_left(){
	bool result = false;
	for(int i = 0; i < field.height; i++){
		for(int j = field.width - 1; j > 0; j--)
			if(field.points[i][j] != 0 && field.points[i][j] == field.points[i][j - 1]){
				field.points[i][j] = 0;
				field.points[i][j - 1] *= 2;
				record.value += field.points[i][j - 1];
				j--;
			}
	}
	return result;
}
bool move_right(){
	bool result = false;
	for(int i = 0; i < field.height; i++){
		for(int j = 0; j < field.width - 1; j++)
			if(field.points[i][j] != 0 && field.points[i][j] == field.points[i][j + 1]){
				field.points[i][j] = 0;
				field.points[i][j + 1] *= 2;
				record.value += field.points[i][j + 1];
				j++;
			}
	}
	return result;
}

bool move_field(int dirrection){
	bool a, b, c;
	switch(dirrection){
		case UP:
			a = sort_up();
			b = move_down();
			c = sort_up();
		break;
		case DOWN:
			a = sort_down();
			b = move_up();
			c = sort_down();
		break;
		case LEFT:
			a = sort_left();
			b = move_right();
			c = sort_left();
		break;
		case RIGHT:
			a = sort_right();
			b = move_left();
			c = sort_right();
		break;
	}
	if(a || b || c)
		set_rand_point();
	if(a || b || c)
		record.steps++;
	return a || b || c;
}

void loadScore(){
	char *fname = "s";
	if(field.width == 4)
		fname = "score_4x4.save";
	if(field.width == 6)
		fname = "score_6x6.save";
	if(field.width == 8)
		fname = "score_8x8.save";
	if( access( fname, F_OK ) == 0 ) {
		FILE *fp = fopen(fname, "r");
		int f;
		fscanf(fp, "%d\n", &f);
		record.max_value = f;
		fclose(fp);
	} else {
		record.max_value = 0;
	}
}

void saveScore(){
	char *fname = "s";
	if(field.width == 4)
		fname = "score_4x4.save";
	if(field.width == 6)
		fname = "score_6x6.save";
	if(field.width == 8)
		fname = "score_8x8.save";
	FILE *f = fopen(fname, "w");
	fprintf(f, "%d\n", record.max_value);
	fclose(f);
}
