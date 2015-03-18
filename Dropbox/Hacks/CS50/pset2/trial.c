#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	bool goodargument;
	string s = GetString() 
	
	for (int i = 0, n = strlen(s); i < n; i++)
	{
		if (isdigit(s[i]) == 0)
		{
			goodargument = false;
			break; 
		}
		else 
		{
			goodargument = true; 
		}	
	}
	printf("good argument? = %d\n", goodargument); 
// check out isdigit() isalpha() isascii() ispunct() isxdigit()
}
