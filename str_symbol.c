#include "shell.h"
/**
 * _strtok - separates strings.
 * 
 * @ln: pointer.
 * @delim: characters mark.
 * Return: pointer.
*/
char *_strtok(char *ln, char *delim)
{
	int n = 0;
	static char *str;
	char *cp_str;

	if (ln != NULL)
		str = ln;
	for (; *str != '\0'; str++)
	{
		while (delim[n] != '\0')
		{
			if (*str == delim[n])
			break;
			n++;
		}
		if (delim[n] == '\0')
			break;
	}
	cp_str = str;
	if (*cp_str == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		n = 0;
		while (delim[n] != '\0')
		{
			if (*str == delim[n])
			{
				*str = '\0';
				str++;
				return (cp_str);
			}
			n++;
		}
	}
	return (cp_str);
}
