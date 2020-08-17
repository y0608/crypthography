#include <stdlib.h>
#include <stdio.h>


//Caesar Shift Cipher
shifting(char* s, int shift)
{
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z' || *s >= 'A' && *s <= 'Z' || *s >= 'a' && *s <= 'z' || *s >= '0' && *s <= '9')//shifting only numbers and letters
		{
			if (*s + shift > 'z' || *s + shift > 'Z')
			{
				if (*s + shift > 'z')
				{
					int toz = 'z' - *s;//spaces to z
					*s = 'a' + toz;
				}
				if (*s + shift > 'Z' && *s + shift <'a')
				{
					int toz = 'Z' - *s;//spaces to Z
					*s = 'A' + toz;
				}
			}
			*s += shift;//Shifting with x positions 
			s++;//Going to next letter
		}
		else
			s++;
	}
}

void main()
{
	char str[100] = "abcdefg";
	int shift = 1;//shifting with x positions
	shifting(str, shift);
}