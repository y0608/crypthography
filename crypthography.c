#include <stdlib.h>
#include <stdio.h>


//Caesar Shift Cipher
shifting(char* s, int shift)
{
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z' || *s >= 'A' && *s <= 'Z' || *s >= 'a' && *s <= 'z' || *s >= '0' && *s <= '9')//shifting only numbers and letters
		{
			if (*s + shift > 'z')
			{
				int toz = 'z' - *s;//spaces to z
				*s = 'a' + shift - toz - 1;
				s++;
			}
			else if (*s + shift > 'Z' && *s + shift <'a')
			{
				int toz = 'Z' - *s;//spaces to Z
				*s = 'A' + shift - toz - 1;
				s++;
			}
			else if (*s + shift > '9' && *s + shift < 'A')
			{
				int to9 = '9' - *s;//spaces to Z
				*s = '0' + shift - to9 - 1;
				s++;
			}
			else
			{
				*s += shift;//Shifting with x positions 
				s++;//Going to next letter
			}
			
		}
		else
			s++;
	}
}

void main(int argc,const char *argv[])
{
	int shift;
	char str[100];
	printf("Enter your code:\n");
	scanf_s("%s", str);
	do
	{
		printf("Enter a number between 0 and 26:\n");
		scanf_s("%d", &shift);
	} while (shift > 25 || shift < 0);
	shifting(str, shift);
	printf("%s\n",str);
}