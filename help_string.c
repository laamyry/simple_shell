#include "shell.h"

/**
 * str_len - string's len.
 *
 * @string: pointer.
 * Return: string's len.
 */
int str_len(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_dupl - duplicator.
 *
 * @string: String.
 * Return: pointer.
 */
char *str_dupl(char *string)
{
	char *res;
	int len, m = 0;

	if (string == NULL)
		return (NULL);

	len = str_len(string) + 1;

	res = malloc(sizeof(char) * len);

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	while (m < len)
	{
		res[m] = string[m];
		m++;
	}

	return (res);
}

/**
 * str_cmp - Compare two strings
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int str_cmp(char *str1, char *str2, int number)
{
	int navigator = 0;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (number == 0)
	{
		if (str_len(str1) != str_len(str2))
			return (0);
		while (str1[navigator])
		{
			if (str1[navigator] != str2[navigator])
			{
				return (0);
			}
			navigator++;
		}
		return (1);
	}
	else
	{
		for (navigator = 0; navigator < number ; navigator++)
		{
			if (str1[navigator] != str2[navigator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_join - concatenates two strings.
 * @str1: String to be concatenated
 * @str2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_join(char *str1, char *str2)
{
	char *res;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_len(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = str_len(str2);

	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	len1 = 0;

	while (str1[len1] != '\0')
	{
		res[len1] = str1[len1];
		len1++;
	}
	free(str1);
	len2 = 0;

	while (str2[len2] != '\0')
	{
		res[len1] = str2[len2];
		len1++;
		len2++;
	}

	res[len1] = '\0';
	return (res);
}


/**
 * flip_str - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void flip_str(char *string)
{

	int m = 0, len = str_len(string) - 1;
	char secure;

	while (m < len)
	{
		secure = string[m];
		string[m++] = string[len];
		string[len--] = secure;
	}
}
