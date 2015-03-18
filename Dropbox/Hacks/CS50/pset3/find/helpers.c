/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)   
{   
    // Error checking, making sure array has min 2 elements.
    if (n <= 0)
	{
		return false;
	}	
	else if (n ==1)
	{ 
		return value == values[0];
	}
		
	// implementing a binary searching algorithm	
    int beginging = 0; 
    int ending = n - 1; 
    
    while (ending >= beginging) 
    {
    	int midpoint = (ending + beginging)/2;
    	
    	if (values[midpoint] == value)
    	{
    		return true;
    	}
    	else if (values[midpoint] > value)
    	{
    		ending = midpoint - 1;
    	}
    	else
    	{
    		beginging = midpoint + 1;
    	}
    } 
    return false;   
 }   

/**
 * Sorts array of n values using bubble sort.
 */
void sort(int values[], int n)
{
    bool notSorted = true;
    while (notSorted)
    {
    	notSorted = false;
    	for (int i = 0; i < n-1; i++)
    	{
    		if (values[i] > values[i+1])
    		{
    			int temp = values[i];
    			values[i] = values[i+1]; 
    			values[i+1] = temp;
    			notSorted = true;
    		}
    	}
    }
}
