/**
 * vigenere.c
 *
 * Anugrah Vijay
 * cooldude_anugrah@hotmail.com
 *
 * Takes in a key word and an input phrase and encrypts using vigeneres cypher.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// prototypes
bool isgoodargument(string);
string makelower(string);

int main(int argc, string argv[])
{
	string key_string;
	string plaintext;
	
	// checks for proper usage
	if (argc != 2)
	{
		printf("Please enter ONE command line argument : ( \n");
		return 1;
	}
	else
	{
		// makes key_string lowercase so that it's easier to manipulate
		key_string = makelower(argv[1]); 
	}
	
	// checks if command line argument meets criteria
	if (isgoodargument(key_string) == false)
	{
		printf("Argument is invalid. Remember alphabetic characters only.\n");
		return 1; 
	}
	
	// prompt loop, until a string is inputed.
	do
	{
		plaintext = GetString(); 
	}
	while (strcmp(plaintext,"") == 0);
	
	int n = strlen(plaintext);
	
	// make key as big as plaintext, solves problem of looping through key
	while (strlen(key_string) <= n)
	{
		strcat(key_string, key_string);
	}
	
	// does the encoding by rotating the alphabet by the value of the current key character.
	for (int i = 0, j = 0; i < n; i++)
	{
		// if lowercase
		if (isalpha(plaintext[i]) && (plaintext[i] >= 'a' && plaintext[i] <= 'z'))
		{
			// Adds value of current key character to plaintext character
			plaintext[i] = plaintext[i] + (key_string[j] - 97);
			// increments only if 
			j++;
			
			if ((unsigned char) plaintext[i] > 122)
			{
				plaintext[i] =  97 + ((unsigned char) plaintext[i] % 122) - 1;
			} 
		}// if uppercase	
		else if (isalpha(plaintext[i]) && (plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
		{
			plaintext[i] = plaintext[i] + (key_string[j] - 97);
			j++;
			
			if ( plaintext[i] > 90)
			{
				plaintext[i] = 65 + ( plaintext[i] % 90) -1;
			}
		}
	}
	printf("%s\n", plaintext);
}


bool isgoodargument(string key)
{
	bool goodargument;
	
	/** 
	 * loops through the key string and checks for non alphabetic characters. 
	 * returns true if argument is good. 
	 */
	for (int i = 0, n = strlen(key); i < n; i++)
	{
		if (isalpha(key[i]) == 0)
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


string makelower(string s)
{
	for (int i = 0, n = strlen(s); i < n; i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}
