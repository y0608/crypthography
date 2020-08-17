#include <stdlib.h>
#include <stdio.h>


//Caesar Shift Cipher
shifting(char* s, int shift)
{
	while (*s)
	{

		if (*s >= 'a' && *s <= 'z' || *s >= 'A' && *s <= 'Z' || *s >= 'a' && *s <= 'z' || *s >= '0' && *s <= '9')//shifting only numbers and letters
		{

			if (*s + shift > 'z')// its a small character ,because from Z(90) to z(122) its 32 spaces, x max is 25 so there is not a problem 
			{
				int toz = 'z' - *s;//spaces to z
				*s = 'a' + toz;
			}

			if (*s + shift > 'Z')// its a capital because if it was a small we would have already checked
			{
				int toz = 'Z' - *s;//spaces to Z
				*s = 'A' + toz;
			}

			if(*s + shift )

			*s += shift;//Shifting with x positions 
			s++;//Going to next letter
		}
		else
			s++;
	}
}

void main()//97-122
		  //65-90/golemi
		 //48-57/cifri
{
	char str[100] = "Prashtame vi 100 leva";
	char test = '9';
	char test2 = '0';
	int shift = 1;//shifting with x positions //max 25
	shifting(str, shift);
}

/*shift(char* s, int x)
{
	while (*s)
	{

		if (*s >= 'a' && *s <= 'z' || *s >= 'A' && *s <= 'Z' || *s >= 'a' && *s <= 'z' || *s >= '0' && *s <= '9')//shifting only numbers and letters
		{
			if (*s + x > 'z' || *s + x > 'Z')
			{
				if (*s >= 'a' && *s <= 's')// if s is capital or not
				{
					int toz = 'z' - *s;//spaces to z
					*s = 'a' + toz;
				}
				else
				{
					int toz = 'Z' - *s;//spaces to Z
					*s = 'A' + toz;
				}

			}
			*s += x;//Shifting with x positions 
			s++;//Going to next letter
		}
		else
			s++;
	}
}

void main()//97-122
		  //65-90/golemi
{
	char str[100] = "Prashtame vi 100 leva";
	int x = 1;//shifting with x positions
	shift(str, x);
}*/