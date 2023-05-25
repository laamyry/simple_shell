#include "shell.h"
/**
 * symbolize - separate string.
 * @data: program's data pointer
 * Return: an array.
 */
void symbolize(program_data *data)
{
	char *separator = " \t";
	int m = 0, n, count = 2, len;

	len = str_len(data->new_line);
	if (len)
	{
		if (data->new_line[len - 1] == '\n')
			data->new_line[len - 1] = '\0';
	}

	while (data->new_line[m])
	{
		for (n = 0; separator[n]; n++)
		{
			if (data->new_line[m] == separator[n])
			{
				count++;
			}
		}
		m++;
	}

	data->symbols = malloc(count * sizeof(char *));
	if (data->symbols == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	m = 0;
	data->symbols[m] = str_dupl(_strtok(data->new_line, separator));
	data->cmd_name = str_dupl(data->symbols[0]);
	while (data->symbols[m++])
	{
		data->symbols[m] = str_dupl(_strtok(NULL, separator));
	}
}
