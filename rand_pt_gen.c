#Written by Akhilesh Balasingam
#include "rand.h"
#include "rand_pt_gen.h"
#include "printf.h"
#include "strings.h"
#include "malloc.h"

#define NUM_ROWS 3
#define NUM_COLS 3
#define NUM_CELLS NUM_ROWS*NUM_COLS

cell* grid;

const char *color_options_a[2] = {"blue", "green"};

const char* color_options_b[2] = {"red", "blue"};

const char* color_options_c[2] = {"red", "green"};

const char* color_options_full[3] = {"red", "green", "blue"};

static unsigned long int next = 1;

int my_rand(){
    next = next*1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

int rand_within_range(int lower, int upper){
    if(lower == 0 && upper == 1) return my_rand() % 2;

    return my_rand() % (upper + 1 - lower) + lower;
}

void debug_dump(cell* grid_f){
    for(int i = 0; i < NUM_CELLS; i++){
        printf("--------------------------\n");
        printf("CELL #%d: \n", i);
        printf("row = %d\n", grid_f[i].row);
        printf("col = %d\n", grid_f[i].col);
        printf("color = %s\n", grid_f[i].color);
        printf("point = %d\n", grid_f[i].point_val);
        printf("--------------------------\n");
    }
}

void assign_points(){
    for(int i = 0; i < NUM_CELLS; i++){
        if(strcmp(grid[i].color, "red") == 0) grid[i].point_val = 10;
        if(strcmp(grid[i].color, "green") == 0) grid[i].point_val = 5;
        if(strcmp(grid[i].color, "blue") == 0) grid[i].point_val = 1;
    }
}

//generate grid
void gen_grid(){
    grid = malloc(NUM_CELLS * sizeof(cell));

    int count = 0;

    for(int row = 0; row < NUM_ROWS; row++){
        for(int col = 0; col < NUM_COLS; col++){
            //create temp var while iterating
            cell new_cell = {0};
            new_cell.col = col; 
            new_cell.row = row;

            //half hard code stuff in
            if(new_cell.row == 0 && (new_cell.col == 0 || new_cell.col == 2)){
                new_cell.color = (char*) color_options_a[rand_within_range(0,1)];
            } else if(new_cell.row == 2 && new_cell.col == 2){
                new_cell.color = (char*) color_options_b[rand_within_range(0,1)];
            } else if(new_cell.row == 1 && new_cell.col == 1){
                new_cell.color = (char*) "red";
            } else if(new_cell.row == 0 && new_cell.col == 1){
                new_cell.color = (char*) color_options_b[rand_within_range(0,1)];
            } else if(new_cell.row == 1 && new_cell.col == 0){
                new_cell.color = (char*) color_options_full[rand_within_range(0,1)];
            } else if(new_cell.row == 2 && new_cell.col == 1){
                new_cell.color = (char*) color_options_c[rand_within_range(0,1)];
            } else if(new_cell.row == 1 && new_cell.col == 2){
                new_cell.color = (char*) color_options_b[rand_within_range(0,1)];
            } else if(new_cell.row == 2 && new_cell.col == 0){
                new_cell.color = (char*) color_options_a[rand_within_range(0,1)];
            }

            //put in big grid array
            grid[count] = new_cell;
            count++;
        }
    }
}

cell* get_grid(){
    gen_grid();
    assign_points();
    return grid;
}
