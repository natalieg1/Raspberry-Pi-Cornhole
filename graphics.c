#Written by Natalie Greenfield
/* This page of code contains modular functions for the graphics and game opperation of 
modified cornhole*/ 

#include "gl.h"
#include "timer.h"
#include "strings.h"
#include "rand_pt_gen.h"
#include "laser.h"
#include "led.h"
#include "graphics.h"
#include "malloc.h"
#include "numstr.h"

#define TURN_TIME 15


//Draws the rules
static void draw_rules(){
    int r_st = 320;//pixel from which the rules start
    gl_draw_string(50, 300, "---------------Rules---------------", GL_WHITE);
    gl_draw_string(10, r_st + 20, "1. Points are randomized for 9 blocks.", GL_WHITE);
    gl_draw_string(10, r_st + 40, "Three levels of points exist (10 -", GL_WHITE);
    gl_draw_string(500, r_st + 40, "red", GL_RED);
    gl_draw_string(545, r_st + 40, ",", GL_WHITE);
    gl_draw_string(10, r_st + 60, "5 - ", GL_WHITE); 
    gl_draw_string(66, r_st + 60, "green", GL_GREEN);
    gl_draw_string(136, r_st + 60, ", 1 - ", GL_WHITE);
    gl_draw_string(220, r_st + 60, "blue", GL_BLUE);
    gl_draw_string(276, r_st + 60, ") and the colors of", GL_WHITE);
    gl_draw_string(10, r_st + 80, "LEDs correspond to point value.", GL_WHITE);
    gl_draw_string(10, r_st + 110, "2. Screen will show point distribution and", GL_WHITE);
    gl_draw_string(10, r_st + 130, "keep tally. Timer will tell you when to", GL_WHITE);
    gl_draw_string(10, r_st + 150,"throw the beanbag.", GL_WHITE);
    gl_draw_string(270, r_st + 150,"3 throws per round.", GL_MAGENTA);
    gl_draw_string(10, r_st + 180,"3. Throw, it will record the corresponding", GL_WHITE);
    gl_draw_string(10, r_st + 200,"point (if any). You must retrieve beanbag", GL_WHITE);
    gl_draw_string(10, r_st + 220,"before other player begins.", GL_WHITE);
}

//draw the current game grid on the screen 
static void draw_board(cell * grid){
    //loop over the array of cells
    for (int i = 0; i < 9; i++){
        int color = 0;

        //determine square color
        if (grid[i].point_val == 1) color = GL_BLUE;
        else if (grid[i].point_val == 5) color = GL_GREEN;
        else if (grid[i].point_val == 10) color = GL_RED;
        
        //draw square in correct position 
        gl_draw_rect(10 + (grid[i].col * 90), 10 + (grid[i].row * 90), 90, 90, color);

        //Draws black spaces between grid blocks 
        gl_draw_rect(97, 10, 6, 270, GL_BLACK);
        gl_draw_rect(187, 10, 6, 270, GL_BLACK);
        gl_draw_rect(10, 97, 270, 6, GL_BLACK);
        gl_draw_rect(10, 187, 270, 6, GL_BLACK);
    } 
}

//draw the update player points table 
static void draw_point_table(points * tally, int player){
    //highlight current player in magenta 
    if (player == 1){
        gl_draw_string(326, 18, "Player 1", GL_MAGENTA);
        gl_draw_string(466, 18, "Player 2", GL_WHITE);
    }
    else if (player == 2){
        gl_draw_string(326, 18, "Player 1", GL_WHITE);
        gl_draw_string(466, 18, "Player 2", GL_MAGENTA);
    }
    
    //change point number to string which can be written to the screen
    char buf1[3];
    char buf2[3];
    char * points_1 = buf1;
    char * points_2 = buf2;
    unsigned_to_base1(points_1, 3, tally->player_1, 10, 0);  
    unsigned_to_base1(points_2, 3, tally->player_2, 10, 0);  

    //draw points to screen
    gl_draw_string(370, 70, points_1, GL_WHITE);
    gl_draw_string(514, 70, points_2, GL_WHITE);

    //draw table outline 
    gl_draw_line(310, 40, 590, 40, GL_BLUE);
    gl_draw_line(310, 10, 590, 10, GL_BLUE);
    gl_draw_line(310, 120, 590, 120, GL_BLUE);
    gl_draw_line(450, 10, 450, 120, GL_BLUE);
    gl_draw_line(310, 10, 310, 120, GL_BLUE);
    gl_draw_line(590, 10, 590, 120, GL_BLUE);
}

//Prepare next screen before player throws beanbag 
static void before_throw_draw_screen(color_t c, cell * grid, points * tally, int player){
    gl_clear(c);
    draw_rules();
    draw_board(grid);
    draw_point_table(tally, player);
}

//Draws the 3,2,1, throw that should display while the player is throwing 
static void draw_throwing(){
    gl_draw_char(330, 180, '3', GL_WHITE);
    gl_draw_char(330 + 50, 180, '2', GL_WHITE);
    gl_draw_char(330 + 100, 180, '1', GL_WHITE);
    gl_draw_string(330 + 150, 180, "Throw!", GL_WHITE);
}

//Updates the screen with the correct points, grid and time left to throw  
static void update_screen(int secs, cell * grid, points * tally, int player){
    before_throw_draw_screen(GL_BLACK, grid, tally, player);//draw grid, points table and rules
    draw_throwing();//draw 3,2,1, throw

    //converts integers seconds to a screen writeable string 
    char buf[3];
    char* num = buf;
    unsigned_to_base1(num, 3, secs, 10, 0); 

    //draw time remaining  
    gl_draw_string(360, 240, "Time left:", GL_WHITE);
    gl_draw_string(510, 240, num, GL_WHITE);
}

//Sequentially draws the sequence "3, 2, 1, throw" by drawing and then swaping the buffer each time
static void ready_to_throw(cell * grid, points * tally, int player){
    before_throw_draw_screen(GL_BLACK, grid, tally, player);
    gl_draw_char(330, 180, '3', GL_WHITE);//draw 3
    gl_swap_buffer();
    timer_delay_ms(300);
    before_throw_draw_screen(GL_BLACK, grid, tally, player);
    gl_draw_char(330, 180, '3', GL_WHITE);
    gl_draw_char(330 + 50, 180, '2', GL_WHITE);//draw 2
    gl_swap_buffer();
    timer_delay_ms(300);
    before_throw_draw_screen(GL_BLACK, grid, tally, player);
    gl_draw_char(330, 180, '3', GL_WHITE);
    gl_draw_char(330 + 50, 180, '2', GL_WHITE);
    gl_draw_char(330 + 100, 180, '1', GL_WHITE);//draw 1
    gl_swap_buffer();
    timer_delay_ms(300);
    //draw timer on screen with throw!
    update_screen(TURN_TIME, grid, tally, player);
    gl_draw_string(330 + 150, 180, "Throw!", GL_WHITE);
    gl_swap_buffer();
}

//  Returns int specifying the the next player.
int update_points(cell * grid, points * tally, int row, int col, int player){
    cell (*grid_2D)[3] = (cell(*)[]) grid; //typecast grid to a 2-D array for easier acess

    //check which player's tally to update
    if (player == 1){
        //use the row and col from where the beanbag landed to access the correct points
        //to add based on the current game grid 
        tally->player_1 += grid_2D[row][col].point_val;
    }
    else if (player == 2){
        //use the row and col from where the beanbag landed to access the correct points 
        //to add based on the current game grid 
        tally->player_2 += grid_2D[row][col].point_val;
    }
    return player;
}

//displays a new screen inbetween each round with the appropriate round number 
static void round_card(int round){
    gl_clear(GL_BLACK);

    //convert round number to a string which can be written to the screen 
    char buf[2];
    char* num = buf;
    unsigned_to_base1(num, 2, round, 10, 0);
    
    //intialize new framebuffer which is smaller so that the text on the scren is larger 
    gl_init(300, 300, GL_DOUBLEBUFFER); 

    //draw round information
    gl_draw_string(60, 100, "Round:", GL_WHITE);
    gl_draw_string(149, 100, num, GL_WHITE);
    gl_draw_string(173, 100, "of 3", GL_WHITE);
    gl_draw_string(30, 200, "Generating Grid...", GL_WHITE);
    gl_swap_buffer();//show round info screen
}

//displays who won at the end of the game! 
static void win_card(points * tally){
    gl_clear(GL_BLACK);
    int player = 0;

    //intialize new framebuffer which is smaller so that the text on the scren is larger 
    gl_init(300, 300, GL_DOUBLEBUFFER); 

    //compare tallies to determine winner 
    if (tally->player_1 > tally->player_2) player = 1;
    else if (tally->player_2 > tally->player_1) player = 2;

    //if both players tie  
    else if (tally->player_2 == tally->player_1){
        gl_clear(GL_BLACK);
        gl_draw_string(120, 145, "TIE!!", GL_GREEN);
        gl_swap_buffer();
        return;
    }

    //turn player number into a string that can be written to the screen  
    char buf[2];
    char* num = buf;

    //write winner message to screen 
    unsigned_to_base1(num, 2, player, 10, 0);
    gl_draw_string(85, 100, "Player", GL_GREEN);
    gl_draw_string(175, 100, num, GL_GREEN);
    gl_draw_string(30, 200, "Is the WINNER!!!", GL_GREEN);
    gl_swap_buffer();//show screen
}

//runs the graphics and game functionality for a player's turn 
static void run_turn(cell * grid, points * tally, int player){
    int time = TURN_TIME;//number of seconds a player has to throw 
    ready_to_throw(grid, tally, player);//display throw countdown

    //check if player has thrown beanbag while their turn time counts down 
    while(time >= 0){
        update_screen(time, grid, tally, player);
        gl_swap_buffer();
  
        //check if a beanbag has been sensed on the board 
        cell check_hit = determine_quadrant_intersection();

        //if beanbag is sensed the cell will contain the col and row in which the bean bag landed 
        //if not sensed the col and row will be equal to 999

        //if beanbag sensed
        if (check_hit.row != 999){
            // update points
            player = update_points(grid, tally, check_hit.row, check_hit.col, player);
            // display the string "Hit!" in the equivilent square on the screen that the beanbag landed on on the board   
            update_screen(time, grid, tally, player);
            gl_draw_string(30 + (check_hit.col * 90), 45 + (check_hit.row * 90),"Hit!", GL_WHITE);//draw hit
            gl_swap_buffer(); 
            timer_delay(3);//pause to show hit on screen 
            //avoid next turn until beanbag removed 
            while(check_hit.row != 999){
                 check_hit = determine_quadrant_intersection();
            }
            // leave and restart timer
            return;
        }

        //if beanbad not sensed wait a second and then reduce the turn time left 
        timer_delay(1);
        time--;
    }
}  

//runs a round of the game
static void run_round(cell * grid, points * tally){
    int player = 1;

    //three throws per player per round 
    for (int turn = 0; turn < 6; turn++){ 
        run_turn(grid, tally, player);//run a turn
        //update which player it is 
        if (player == 1) player = 2;
        else if (player == 2) player = 1;
    }
} 

//runs a full game 
void run_game(color_t c){
    gl_clear(c);
    points * tally = malloc(8);//malloc space for points struct 

    //set initial tally values
    tally->player_1 = 0;
    tally->player_2 = 0;

    //run three game rounds
    for(int round = 1; round < 4; round++) { 
        round_card(round);//show round card
        cell * grid = get_grid();//get a new random grid 
        //display a bunch of random grids on the gameboard LED's while generating the game grid for the round 
        for(int i = 0; i < 35; i++){
            turn_on_grid(grid);//display the lights for the grid on our physical game board 
            timer_delay_ms(100);
            turn_off_grid(grid);//turn off the lights for the grid on our physical game board
            grid = get_grid();//get a new random grid
        }
        gl_init(600, 600, GL_DOUBLEBUFFER); //intialize the framebuffer for the game graphics
        grid = get_grid();//get grid for the game round 
        turn_on_grid(grid);//turn on the LED's for that grid
        run_round(grid, tally);//run a round 
        turn_off_grid(grid);//turn off the LED's for that round 
        
    }
    win_card(tally);//once the game is over show the win card 
}
