/**
 * caesar.c
 *
 * Anugrah Vijay
 * cooldude_anugrah@hotmail.com
 *
 * Takes in a numeric key and an input phrase and encrypts using caesars cypher.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// prototypes
bool isgoodargument(string);

int main(int argc, string argv[])
{	
    int key;
    string key_string;
    string plaintext;
	
	// checks to see if only one command line argument. 
	if (argc != 2)
	{
		printf("Please enter ONE command line argument : ( \n");
		return 1;
	}
	else
	{
		key_string = argv[1]; 
		key = atoi(key_string) % 26;
	}
	
	// checks to see if key entered is positive integer.
	if (isgoodargument(key_string) == false)
	{
		printf("Argument is invalid. Remember positive integer only.\n");
		return 1; 
	}
	
	// asks user for plaintext until input is provided.
	do
	{
		plaintext = GetString(); 
	}
	while (strcmp(plaintext,"") == 0);
	
	// does the encoding by rotating the alphabets by the value of the key.
	for (int i = 0, n = strlen(plaintext); i < n; i++)
	{
		// if lowercase
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
		{
			plaintext[i] = ((int) plaintext[i] + key);
			
			// unsigned char used because if you use regular char, the ASCII value becomes negative.
			if ((unsigned char) plaintext[i] > 122)
			{
				plaintext[i] = 97 + ((unsigned char) plaintext[i] % 122) - 1;
			
			}
		}
		// if uppercase 
		else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
		{
			plaintext[i] = (plaintext[i] + key);
			if (plaintext[i] > 90)
			{
				plaintext[i] = 65 + (plaintext[i] % 90) - 1;
			}
		}
		else
		{
			continue;
		}
	}
	
	// prints encoded plaintext
	printf("%s\n", plaintext);
	return 0;
}

bool isgoodargument(string key)
{
	bool goodargument;
	
	/** 
	 * loops through the key string and checks for non numeric characters. 
	 * returns true if argument is good. 
	 */
	for (int i = 0, n = strlen(key); i < n; i++)
	{
		if (isdigit(key[i]) == 0)
		{
			goodargument = false;
			break; 
		}
		else 
		{
			goodargument = true; 
		}	
	}
	return goodargument; 
}
