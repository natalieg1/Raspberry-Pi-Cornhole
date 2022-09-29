#Written by Natalie Greenfield
#include "printf.h"
#include "uart.h"
#include "timer.h"
#include "gl.h"
#include "graphics.h"
#include "led.h"
#include "laser.h"


const int WIDTH = 600;
const int HEIGHT = 600;

void main(void)
{
    gl_init(WIDTH, HEIGHT, GL_DOUBLEBUFFER);
    laser_init();
    led_init();
    run_game(GL_BLACK);
    timer_delay(3);    
    uart_init();    
    uart_putchar(EOT);
}
