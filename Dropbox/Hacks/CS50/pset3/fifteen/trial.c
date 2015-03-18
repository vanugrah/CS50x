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

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./trial d\n");
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
    draw();
    
    
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


// make sure that if your printing one digit, you have an additional space
void draw(void)
{
    printf("\n");
    for (int i = 0; i < d; i++)
    {
    	for (int j = 0; j < d ; j++)
    	{
    		if (board[i][j] == 95)
    		{
    			printf("%c  ", ( char) board[i][j]);
    		}
    		else if (board[i][j] > 9)
    		{
				printf("%d  ", board[i][j]);
    		}
    		else
    		{
    			printf("%d   ", board[i][j]);
    		} 
    				
    		if (j == d-1)
    		{
    			printf("\n\n");
    		}
    	}
    }
}  

