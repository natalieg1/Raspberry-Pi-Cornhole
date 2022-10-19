<<<<<<< HEAD
# akhileshvb-natalieg1-project
=======
## Project title: Modified Cornhole

## Team members: Akhilesh Balasingam, Natalie Greenfield 

## Project description
We created a two-player modified cornhole game which uses a grid of laser diodes
 and phototransistors to detect where the beanbag lands, via intersection.

The rules are as follows:
1. Points are randomized for 9 blocks. Three levels of points exist (10 - red, 
5 - green, 1 - blue) and the colors of LEDs correspond to point value.
2. Screen will show point distribution and keep tally. Timer will tell you when 
to throw the beanbag. You will have 15 seconds to throw the beanbag. Each player
gets 3 throws per round and there are three rounds.
3. Throw, it will record the corresponding point (if any). You must retrieve beanbag
 before other player begins.

The points/colour grid is pseudo-randomly generated for each round. The grid is
displayed on the the physical game board through lighting up the appropriate LED's 
and also displayed on the game screen. The timer and "3,2,1, Throw!" animation on
the screen tells the player when to throw. The points of each player depend both  
on which square the beanbag lands on and which game grid has been randomly generated
for current round. The player points talley is shown on the screen and kept track 
of throughout the game so that the winner(or tie) can be announced at the end!!

We have several code modules:

lasers.c - contains functions to check laser beam interrupt at given pin and identify cell containing intersection (and more)

led.c - contains functions to turn on grid given randomly generated grid of points/colors

rand_pt_gen.c - contains several functions to generate random grid of points/colors

graphics.c - contains the code to run the game as well as the graphics for the game

project-app.c - this contains our main function that is called by make run 

Hope you enjoy!! :) 


## References
The following were helpful with our random number generator [1] and understanding how our laser works [2].
[1] https://stackoverflow.com/questions/4768180/rand-implementation
[2] https://www.codrey.com/electronic-circuits/the-mysterious-laser-receiver-sensor-module/

>>>>>>> 9caaa12217440953a99ec80c87c1cb7773e19cc1
