//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle dimensions
#define PAD_LEN 100
#define PAD_HEIGHT 12

// radius of ball
#define RAD 20

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRoundRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    sendToFront(ball);

    // instantiate paddle, centered at bottom of window
    GRoundRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // velocity of ball in x direction
    double x_velocity =  drand48() + 1;
    
    // velocity of ball in y direction
    double y_velocity = drand48() + 1; 

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
         
             
        if (event != NULL)
        {
        	if (getEventType(event) == MOUSE_MOVED)
        	{
        		double mouseX = getX(event); 
        		
        		if (mouseX < PAD_LEN/2)
        		{
        			mouseX = PAD_LEN/2;
        		}
        		else if(mouseX > (WIDTH - PAD_LEN/2))
        		{
        			mouseX = WIDTH - PAD_LEN/2;
        		}	
        		setLocation(paddle, mouseX - PAD_LEN/2, getY(paddle)); 
        	}
        }
        
       // getting the ball to move   
       move(ball,x_velocity,y_velocity); 
       
       // making ball bounce of edges
       if (getX(ball) <= 0)
       {
           x_velocity = -x_velocity;
       }
       else if ((getX(ball) + getWidth(ball)) >= WIDTH)
       {
           x_velocity = -x_velocity;
       }
       else if (getY(ball) <= 0)
       {
           y_velocity = -y_velocity;
       }
       else if ((getY(ball) + getWidth(ball)) >= HEIGHT)
       {
           lives--; 
           setLocation(ball, WIDTH/2 - RAD, HEIGHT/2);
           x_velocity =  drand48() + 1;
           y_velocity =  drand48() + 1;
           pause(500);
           move(ball,x_velocity,y_velocity);                
       }
       
       // making the ball bounce of paddle
       GObject object = detectCollision(window, ball);         
       if (object != NULL)
       {
           if (object == paddle)
           {
               y_velocity = -y_velocity;
           }
           else if (strcmp(getType(object), "GRect") == 0)
           {           
                // make 4 gobjects, and check all 4 sides of the ball for bricks. 
                GObject up = getGObjectAt(window, getX(ball) + RAD, getY(ball));
                GObject down = getGObjectAt(window, getX(ball) + RAD, getY(ball) + getWidth(ball));
                GObject left = getGObjectAt(window, getX(ball), getY(ball) + RAD);
                GObject right = getGObjectAt(window, getX(ball) + getWidth(ball), getY(ball) + RAD);


               if (up != NULL)
               {
                   removeGWindow(window, up);
                   y_velocity = -y_velocity;
                   points++; 
                   bricks--;  
                   printf("%d\n", bricks);
                   updateScoreboard(window, label, points);               
               }
               else if (down != NULL)
               {
                   removeGWindow(window, down);
                   y_velocity = -y_velocity; 
                   points++;
                   bricks--;
                   printf("%d\n", bricks);
                   updateScoreboard(window, label, points);                                  
               }
               else if (left != NULL)
               {
                   removeGWindow(window, left);
                   x_velocity = -x_velocity;   
                   points++;
                   bricks--; 
                   printf("%d\n", bricks);
                   updateScoreboard(window, label, points);             
               }               
               else if (right != NULL)
               {
                   removeGWindow(window, right);
                   x_velocity = -x_velocity; 
                   points++;
                   bricks--;
                   printf("%d\n", bricks);
                   updateScoreboard(window, label, points);            
               }                                      
           }
       }  
       pause(7); 
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{	// distance between cols = 3, distance between borders = 2,1 , distance between rows 
    
    for (int j = 0; j < ROWS; j++)
    {
        for (int i = 0; i < COLS; i++)
    	{
    		char* str_arr[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};
    		GRect brick = newGRect(2 + i*(40), 50 + j*(15), 35, 10);
    		add(window, brick); 
    		setColor(brick, str_arr[j]);
    		setFilled(brick, true);
    	}
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2 - RAD, HEIGHT/2 - RAD, RAD, RAD);
    add(window, ball); 
    setColor(ball, "DARK_GRAY");
    setFilled(ball, true);
    
    return ball; 
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRoundRect initPaddle(GWindow window)
{ // 150, 550
    GRoundRect paddle = newGRoundRect((WIDTH - PAD_LEN)/2, HEIGHT -(5*PAD_HEIGHT), PAD_LEN, PAD_HEIGHT,15);
    add(window, paddle); 
    setColor(paddle, "DARK_GRAY");
    setFilled(paddle, true);
    setFillColor(paddle, "GRAY");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
      GLabel label = newGLabel("0");
      setFont(label, "SansSerif-42");
      setColor(label, "LIGHT_GRAY");
      double x = (getWidth(window) - getWidth(label)) / 2;
      double y = (getHeight(window) - getHeight(label)) / 2;
      setLocation(label, x, y);
      add(window, label);
      sendToBack(label);
      
      return label;
      
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
