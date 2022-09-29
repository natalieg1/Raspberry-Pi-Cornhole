#Written by Akhilesh Balasingam
#ifndef LED_H
#define LED_H

#include "gpio.h"
#include "rand_pt_gen.h"

enum {
    LED_00_GREEN = GPIO_PIN10,
    LED_00_BLUE = GPIO_PIN9,
    LED_01_RED = GPIO_PIN11,
    LED_01_BLUE = GPIO_PIN5,
    LED_02_BLUE = GPIO_PIN6,
    LED_02_GREEN = GPIO_PIN13,
    LED_10_RED = GPIO_PIN19,
    LED_10_GREEN = GPIO_PIN26,
    LED_10_BLUE = GPIO_PIN18,
    LED_11_RED = GPIO_PIN23,
    LED_12_RED = GPIO_PIN24,
    LED_12_BLUE = GPIO_PIN25,
    LED_20_GREEN = GPIO_PIN8,
    LED_20_BLUE = GPIO_PIN7,
    LED_21_RED = GPIO_PIN12,
    LED_21_GREEN = GPIO_PIN16,
    LED_22_RED = GPIO_PIN20,
    LED_22_BLUE = GPIO_PIN21,
} led_pins;


void led_init();
void turn_on_cell(cell cell_in_q);
void turn_off_cell(cell cell_in_q);
void turn_on_grid(cell* grid);
void turn_off_grid(cell* grid);

#endif
