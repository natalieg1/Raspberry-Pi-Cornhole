#Written by Akhilesh Balasingam
#include "led.h"
#include "rand_pt_gen.h"
#include "strings.h"

#define NUM_ROWS 3
#define NUM_COLS 3
#define NUM_CELLS NUM_ROWS*NUM_COLS

void led_init(){
    gpio_set_function(9,GPIO_FUNC_OUTPUT);
    gpio_set_function(10,GPIO_FUNC_OUTPUT);
    gpio_set_function(11,GPIO_FUNC_OUTPUT);
    gpio_set_function(5,GPIO_FUNC_OUTPUT);
    gpio_set_function(6,GPIO_FUNC_OUTPUT);
    gpio_set_function(13,GPIO_FUNC_OUTPUT);
    gpio_set_function(19,GPIO_FUNC_OUTPUT);
    gpio_set_function(26,GPIO_FUNC_OUTPUT);
    gpio_set_function(18,GPIO_FUNC_OUTPUT);
    gpio_set_function(23,GPIO_FUNC_OUTPUT);
    gpio_set_function(24,GPIO_FUNC_OUTPUT);
    gpio_set_function(25,GPIO_FUNC_OUTPUT);
    gpio_set_function(8,GPIO_FUNC_OUTPUT);
    gpio_set_function(7,GPIO_FUNC_OUTPUT);
    gpio_set_function(12,GPIO_FUNC_OUTPUT);
    gpio_set_function(16,GPIO_FUNC_OUTPUT);
    gpio_set_function(20,GPIO_FUNC_OUTPUT);
    gpio_set_function(21,GPIO_FUNC_OUTPUT);
}

void turn_on_cell(cell cell_in_q){
    int row = cell_in_q.row;
    int col = cell_in_q.col;
    char* color = cell_in_q.color;

    if(row == 0 && col == 0){
        if(strcmp(color, "blue") == 0) gpio_write(LED_00_BLUE, 1);
        if(strcmp(color, "green") == 0) gpio_write(LED_00_GREEN, 1);
    } else if(row == 0 && col == 1){
        if(strcmp(color, "red") == 0) gpio_write(LED_01_RED, 1);
        if(strcmp(color, "blue") == 0) gpio_write(LED_01_BLUE, 1);
    } else if(row == 0 && col == 2){
        if(strcmp(color, "blue") == 0) gpio_write(LED_02_BLUE, 1);
        if(strcmp(color, "green") == 0) gpio_write(LED_02_GREEN, 1);
    } else if(row == 1 && col == 0){
        if(strcmp(color, "red") == 0) gpio_write(LED_10_RED, 1);
        if(strcmp(color, "blue") == 0) gpio_write(LED_10_BLUE, 1);
        if(strcmp(color, "green") == 0) gpio_write(LED_10_GREEN, 1);
    } else if(row == 1 && col == 1){
        if(strcmp(color, "red") == 0) gpio_write(LED_11_RED, 1);
    } else if(row == 1 && col == 2){
        if(strcmp(color, "red") == 0) gpio_write(LED_12_RED, 1);
        if(strcmp(color, "blue") == 0) gpio_write(LED_12_BLUE, 1);
    } else if(row == 2 && col == 0){
        if(strcmp(color, "green") == 0) gpio_write(LED_20_GREEN, 1);
        if(strcmp(color, "blue") == 0) gpio_write(LED_20_BLUE, 1);
    } else if(row == 2 && col == 1){
        if(strcmp(color, "red") == 0) gpio_write(LED_21_RED, 1);
        if(strcmp(color, "green") == 0) gpio_write(LED_21_GREEN, 1);
    } else if(row == 2 && col == 2){
        if(strcmp(color, "red") == 0) gpio_write(LED_22_RED, 1);
        if(strcmp(color, "blue") == 0) gpio_write(LED_22_BLUE, 1);
    }
}

void turn_off_cell(cell cell_in_q){
    int row = cell_in_q.row;
    int col = cell_in_q.col;
    char* color = cell_in_q.color;

    if(row == 0 && col == 0){
        if(strcmp(color, "blue") == 0) gpio_write(LED_00_BLUE, 0);
        if(strcmp(color, "green") == 0) gpio_write(LED_00_GREEN, 0);
    } else if(row == 0 && col == 1){
        if(strcmp(color, "red") == 0) gpio_write(LED_01_RED, 0);
        if(strcmp(color, "blue") == 0) gpio_write(LED_01_BLUE, 0);
    } else if(row == 0 && col == 2){
        if(strcmp(color, "blue") == 0) gpio_write(LED_02_BLUE, 0);
        if(strcmp(color, "green") == 0) gpio_write(LED_02_GREEN, 0);
    } else if(row == 1 && col == 0){
        if(strcmp(color, "red") == 0) gpio_write(LED_10_RED, 0);
        if(strcmp(color, "blue") == 0) gpio_write(LED_10_BLUE, 0);
        if(strcmp(color, "green") == 0) gpio_write(LED_10_GREEN, 0);
    } else if(row == 1 && col == 1){
        if(strcmp(color, "red") == 0) gpio_write(LED_11_RED, 0);
    } else if(row == 1 && col == 2){
        if(strcmp(color, "red") == 0) gpio_write(LED_12_RED, 0);
        if(strcmp(color, "blue") == 0) gpio_write(LED_12_BLUE, 0);
    } else if(row == 2 && col == 0){
        if(strcmp(color, "green") == 0) gpio_write(LED_20_GREEN, 0);
        if(strcmp(color, "blue") == 0) gpio_write(LED_20_BLUE, 0);
    } else if(row == 2 && col == 1){
        if(strcmp(color, "red") == 0) gpio_write(LED_21_RED, 0);
        if(strcmp(color, "green") == 0) gpio_write(LED_21_GREEN, 0);
    } else if(row == 2 && col == 2){
        if(strcmp(color, "red") == 0) gpio_write(LED_22_RED, 0);
        if(strcmp(color, "blue") == 0) gpio_write(LED_22_BLUE, 0);
    }
}

void turn_on_grid(cell* grid){
    for(int i = 0; i < NUM_CELLS; i++){
        turn_on_cell(grid[i]);
    }
}

void turn_off_grid(cell* grid){
    for(int i = 0; i < NUM_CELLS; i++){
        turn_off_cell(grid[i]);
    }
}
