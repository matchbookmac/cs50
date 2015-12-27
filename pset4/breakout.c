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

// size of paddle
#define PHIGH 10 
#define PWIDE 60 

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
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

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // Set the ball's velocity
    double xvelocity = 4.5 * drand48();
    double yvelocity = 3.0;
    
    // Wait for user
    waitForClick();

    // Set y axis for paddle
    double y = getHeight(window) / 12 * 11 - PHIGH;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // Check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // If there was an event
        if (event != NULL)
        {
            // If the event was a mouse movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // Move the paddle to the x of the mouse
                double x = getX(event) - PWIDE / 2;
                setLocation(paddle, x, y);
            }
        }
        
        // Move the ball
        move(ball, xvelocity, yvelocity);
        
        // Bounce off left
        if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }

        // Bounce off right
        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }

        // Bounce off top
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }

        // Hit bottom you die
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            if (lives > 1)
            {
                setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
                lives--;
                pause(500);
                waitForClick();
            }
            else if (lives <= 1)
            {
                setLocation(ball, getX(ball), getY(ball));
                lives--;
            }
        }

        // Linger
        pause(10);
        
        // Detect collision of ball
        GObject object = detectCollision(window, ball);

        if (object != NULL)
        {
            // If the ball collided with the paddle, turn
            if (object == paddle)
            {
                setLocation(ball, getX(ball), y - 2 * RADIUS);
                yvelocity = -yvelocity;
            }
            // If it collided with a brick flip it and reverse it
            else if (strcmp(getType(object), "GRect") == 0)
            {
                yvelocity = -yvelocity;
                removeGWindow(window, object);
                points++;
                bricks--;
                updateScoreboard(window, label, points);
            }
        }
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
{
    // Let's get an array of pointers for bricks
    GRect* bricks[50];

    // Start making them somewhere
    int x = 2;
    int y = getHeight(window) / 12;

    // Determine their size
    int width = (WIDTH - 10) / 11;
    int height = PHIGH;
    
    // Set color
    char* color = "RED";

    // It's a BRICK... house
    for(int i = 1; i <= ROWS; i++)
    {
        // Determine color of the row
        if (i == 2)
        {
            color = "ORANGE";
        }
        if (i == 3)
        {
            color = "YELLOW";
        }
        if (i == 4)
        {
            color = "GREEN";
        }
        if (i == 5)
        {
            color = "CYAN";
        }
        
        // Print bricks
        for(int j = 1; j <= COLS; j++)
        {
            bricks[i] = newGRect(x, y, width, height);
            setFilled(bricks[i], true);
            setColor(bricks[i], color);
            add(window, bricks[i]);
            x = x + width + width / 7;
        }
        
        // Set coordinates for next row
        y = y + PHIGH + width / 7;
        x = 2;

    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // Determine x and y based on window size
    int x = getWidth(window) / 2 - RADIUS;
    int y = getHeight(window) / 2 - RADIUS;
    
    // Instantiate ball
    GOval ball = newGOval(x, y, 2 * RADIUS, 2 * RADIUS);
    setFilled(ball, true);
    setColor(ball, "BLACK");

    // Add ball to the window
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Determines x and y based on window size
    int x = getWidth(window) / 2 - PWIDE / 2;
    int y = getHeight(window) / 12 * 11 - PHIGH;

    // Instantiates the paddle
    GRect paddle = newGRect(x, y, PWIDE, PHIGH);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");

    // Adds paddle to the window
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // Creates scoreboard
    GLabel score = newGLabel("0 ");
    
    // Sets position color size and font
    double x =  (getWidth(window) / 2) - getWidth(score);
    double y = (getHeight(window) / 2) - getHeight(score);
    setLocation(score, x, y);
    setColor(score, "LIGHT_GRAY");
    setFont(score, "sans_serif-bold-34");
    
    // Put it in there
    add(window, score);
    return score;
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
