#Written by Akhilesh Balasingam
#ifndef LASER_H
#define LASER_H

#include "rand_pt_gen.h"

enum laser_pins {
    LASER_PIN_COL0 = 2,
    LASER_PIN_COL1 = 3,
    LASER_PIN_COL2 = 4,

    LASER_PIN_ROW0 = 17,
    LASER_PIN_ROW1 = 27,
    LASER_PIN_ROW2 = 22,
};

void laser_init();

int check_laser_beam_interrupt(int gpio_pin);
cell determine_quadrant_intersection();

#endif
