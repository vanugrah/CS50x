#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
	float change;
	int coin_counter = 0; 
	int ichange;
    
    // asks for change owed until criteria is met. 
    do 
    {
        printf("O hai! How much change is owed?\n"); 
        change = GetFloat();   
    }
    while (change < 0);
    
    ichange = roundf(change * 100);
    
    // subtracts coin values until change is 0.
    while (ichange > 0)
    {
    	if (ichange >= 25)
    	{
    		ichange = ichange - 25;
    		coin_counter++;
    	}
    	else if (ichange >= 10)
    	{
    		ichange = ichange - 10;
    		coin_counter++;
    	}
    	else if (ichange >= 5)
    	{
    		ichange = ichange - 5;
    		coin_counter++;
    	}
    	else
    	{
    		ichange = ichange - 1;
    		coin_counter++; 
    	}
    }
    
	printf("%d\n",coin_counter); 
}
