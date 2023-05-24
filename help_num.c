#include "shell.h"
/**
 * long_str - number to string.
 * 
 * @number: convert number.
 * @string: buffer string.
 * @base: converting base.
 * Return: Nothing.
 */
void long_str(long number, char *string, int base)
{
	int index = 0, negative = 0;
	long quotient = number;
	char lttrs[] = {"0123456789abcdef"};

	if (quotient == 0)
		string[index++] = '0';

	if (string[0] == '-')
		negative = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[index++] = lttrs[-(quotient % base)];
		else
			string[index++] = lttrs[quotient % base];
		quotient /= base;
	}
	if (negative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}


/**
 * _atoi - string to integer.
 * 
 * @s: pointer string .
 * Return: int or 0.
 */
int _atoi(char *s)
{
	int mark = 1;
	unsigned int number = 0;

	for (; !('0' <= *s && *s <= '9') && *s != '\0'; s++)
	{
		if (*s == '-')
			mark *= -1;
		if (*s == '+')
			mark *= +1;
	}

	for (; '0' <= *s && *s <= '9' && *s != '\0'; s++)
	{
		number = (number * 10) + (*s - '0');
	}
	return (number * mark);
}

/**
 * char_counter - count character.
 *
 * @string: pointer .
 * @character: string.
 * Return: int or 0.
 */
int char_counter(char *string, char *character)
{
	int n = 0, count = 0;

	while (string[n])
	{
		if (string[n] == character[0])
		{
			count++;
		}
		n++;
	}
	return (count);
}
