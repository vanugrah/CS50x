/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();


    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    if ( (d * d) % 2 == 1)
    {
        for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < d; j++)
			{
				if (j == d-1 && i == d-1)
				{
					board[i][j] = 95;
					break;
				}
				board[i][j] = (d * d) - (j + 1) -(i * d); // must not print last item. 
			}
		}
    }
    else 
    {
    	for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < d; j++)
			{
				if (j == d-1 && i == d-1)
				{
					// 95 is the ASCII code for underscore.
					board[i][j] = 95;
					break;
				}
				board[i][j] = (d * d) - (j + 1) -(i * d); // must not print last item. 
			}
		}	
		// reverse 1 and 2, if the board dimensions are even. 
		int temp = board[d-1][d-3];
		board[d-1][d-3] = board[d-1][d-2];
		board[d-1][d-2] = temp; 			
    }
}



/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n");
    for (int i = 0; i < d; i++)
    {
    	for (int j = 0; j < d ; j++)
    	{
    		if (board[i][j] == 95)
    		{
    			printf(" %c  ", ( char) board[i][j]);
    		}
    		else if (board[i][j] > 9)
    		{
				printf("%d  ", board[i][j]);
    		}
    		else
    		{
    			printf(" %d  ", board[i][j]);
    		} 
    				
    		if (j == d-1)
    		{
    			printf("\n\n");
    		}
    	}
    }
} 



/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // determine indicies that border the empty space / and depending on which indicies the tile is at; they move opposite that direction
    
    int free_i;
    int free_j;
    int directions[] = {1,1,1,1}; // in the form of up down left right
    int goodvalues[] = {0,0,0,0};
    
    //finds index of free space
    for (int i = 0; i < d; i++)
    {
    	for (int j = 0; j < d; j++)
    	{
    		if (board[i][j] == 95)
    		{
    			free_i = i;
    			free_j = j;
    		}
    	}
    }
    
    // check to see which all directions possible moves can occur in. 
    if (free_i == 0 )
		directions[0] = -1;
	if (free_i == d-1)
		directions[1] = -1;
	if (free_j == 0)
		directions[2] = -1;
	if (free_j == d-1)
		directions[3] = -1;
    
	// determining which tiles numbers are acceptable values
   	if (directions[0] > 0)
   		goodvalues[0] = board[free_i-1][free_j]; 
    if (directions[1] > 0)
		goodvalues[1] = board[free_i+1][free_j];
	if (directions[2] > 0)
		goodvalues[2] = board[free_i][free_j-1];
	if (directions[3] > 0)
		goodvalues[3] = board[free_i][free_j+1];	
    
    // checks if argument passed in move() is valid.
    if (tile != goodvalues[0] && tile != goodvalues[1] && tile != goodvalues[2] && tile != goodvalues[3])
    	return false;
    
    // does the swap	
    	if (goodvalues[0] == tile && directions[0] > 0)
    	{
    		board[free_i][free_j] = tile;
    		board[free_i-1][free_j] = 95;
    		return true;
    	}
    	else if (goodvalues[1] == tile && directions[1] > 0)
    	{
    		board[free_i][free_j] = tile;
    		board[free_i+1][free_j] = 95;   
    		return true; 	
    	}
    	else if (goodvalues[2] == tile && directions[2] > 0)
    	{
    		board[free_i][free_j] = tile;
    		board[free_i][free_j-1] = 95;  
    		return true;  	
    	}
    	else
    	{
    		board[free_i][free_j] = tile;
    		board[free_i][free_j+1] = 95; 
    		return true;   	
    	}

}




/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
	int solution[d][d];
	bool win = true;
	
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
		{
			if (i == d-1 && j == d-1)
			{
				solution[i][j] = 95;
			}
			else
			{
				solution[i][j] = 1 + j + d*i;
			}
		}
	}	
	
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
		{
			if (win == false)
				break; 
				
			if (solution[i][j] == board[i][j])
			{
				win = true;
			}
			else
			{
				win = false;
				break;
			}
		}
	}
	return win;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
