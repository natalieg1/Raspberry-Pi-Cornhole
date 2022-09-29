#Written by Akhilesh Balasingam
#include "laser.h"
#include "gpio.h"

#define NUM_ROWS 3
#define NUM_COLS 3

int pin_arr[6] = {
    LASER_PIN_COL0,
    LASER_PIN_COL1,
    LASER_PIN_COL2,

    LASER_PIN_ROW0,
    LASER_PIN_ROW1,
    LASER_PIN_ROW2
};

void laser_init(){
    for(int i = 0; i < (NUM_ROWS + NUM_COLS); i++){
        gpio_set_function(pin_arr[i], GPIO_FUNC_INPUT);
    }
}

int check_laser_beam_interrupt(int gpio_pin){
    return !gpio_read(gpio_pin);
}

static cell get_pin_numbers(cell pos_on_board){
    int cur_col = pos_on_board.col;
    int cur_row = pos_on_board.row;

    cell pin_numbers = {0};
    pin_numbers.col = pin_arr[cur_col];
    pin_numbers.row = pin_arr[NUM_ROWS + cur_row];
    return pin_numbers;
}

cell identify_intx_on_grid(cell intx_coord){
    cell* grid = get_grid();
    for(int i = 0; i < NUM_ROWS*NUM_COLS; i++){
        if(grid[i].row == intx_coord.row && grid[i].col == intx_coord.col){
            return grid[i];
        }
    }

   cell blank_blank = {0};
   return blank_blank;
}

cell determine_quadrant_intersection(){
    cell intx_coord = {0};
    for(int row = 0; row < NUM_ROWS; row++){
        for(int col = 0; col < NUM_COLS; col++){
            cell temp = {0};
            temp.col = col;
            temp.row = row;

            cell pin_numbers = get_pin_numbers(temp);

            if(check_laser_beam_interrupt(pin_numbers.col) && check_laser_beam_interrupt(pin_numbers.row)){
                //We have a hit
                intx_coord.col = row;
                intx_coord.row = col;
                return identify_intx_on_grid(intx_coord);
            }
        }
    }
    intx_coord.row = 999;
    intx_coord.col = 999;
    return intx_coord;
}

