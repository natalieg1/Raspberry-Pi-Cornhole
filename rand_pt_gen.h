#Written by Akhilesh Balasingam
#ifndef RAND_PT_GEN_H
#define RAND_PT_GEN_H

typedef struct {
    int row;
    int col;
    int point_val;
    char* color;
} cell;


int rand_within_range(int upper, int lower);

void debug_dump();
void gen_grid();
void assign_points();
cell* get_grid();

#endif
