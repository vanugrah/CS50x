/**
 * mario.c
 *
 * Anugrah Vijay
 * cooldude_anugrah@hotmail.com
 *
 * Makes the mario half-pyramid of a user specified height. 
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height; 
    int height_counter;
    int spaces;
    int hash;
    
    // ask for height until criteria is met
    do 
    {
        printf("Height: "); 
        height = GetInt();   
    }
    while (height > 23 || height < 0);
               
    hash = 2;
    height_counter = height; 
              
    while (height_counter != 0)
    {
        spaces = height - hash + 1;         
        // prints spaces 
        for (int j = 0; j < spaces; j++)
        {   
            printf(" ");
        }        

        // prints hashes
        for (int i = 0; i < hash; i++)
        {
            if (hash == (i+1))
            {
                printf("#\n"); 
            }
            else 
            {
                printf("#");
            }
        }  
                      
        height_counter -= 1;
        hash += 1;
    }
    
    return 0;
}
