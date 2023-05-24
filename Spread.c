#include "shell.h"
/**
 * extend_var - extend variables.
 *
 * @data: program's data pointer.
 * Return: nothing.
 */
void extend_var(program_data *data)
{
	int m, n;
	char line[BUFFER_SIZE] = {0}, spread[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->new_line == NULL)
		return;
	add_buf(line, data->new_line);
	for (m = 0; line[m]; m++)
		if (line[m] == '#')
			line[m--] = '\0';
		else if (line[m] == '$' && line[m + 1] == '?')
		{
			line[m] = '\0';
			long_str(errno, spread, 10);
			add_buf(line, spread);
			add_buf(line, data->new_line + m + 2);
		}
		else if (line[m] == '$' && line[m + 1] == '$')
		{
			line[m] = '\0';
			long_str(getpid(), spread, 10);
			add_buf(line, spread);
			add_buf(line, data->new_line + m + 2);
		}
		else if (line[m] == '$' && (line[m + 1] == ' ' || line[m + 1] == '\0'))
			continue;
		else if (line[m] == '$')
		{
			for (n = 1; line[m + n] && line[m + n] != ' '; n++)
				spread[n - 1] = line[m + n];
			tmp = env_key(spread, data);
			line[m] = '\0', spread[0] = '\0';
			add_buf(spread, line + m + n);
			tmp ? add_buf(line, tmp) : 1;
			add_buf(line, spread);
		}
	if (!str_cmp(data->new_line, line, 0))
	{
		free(data->new_line);
		data->new_line = str_dupl(line);
	}
}
/**
 * extend_alias - Extend aliases.
 * @data: program's data pointer.
 *
 * Return: nothing.
 */
void extend_alias(program_data *data)
{
	int m = 0, n, extended = 0;
	char line[BUFFER_SIZE] = {0}, spread[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->new_line == NULL)
		return;

	add_buf(line, data->new_line);

	while (line[m])
	{
		for (n = 0; line[m + n] && line[m + n] != ' '; n++)
			spread[n] = line[m + n];
		spread[n] = '\0';

		tmp = obt_alias(data, spread);
		if (tmp)
		{
			spread[0] = '\0';
			add_buf(spread, line + m + n);
			line[m] = '\0';
			add_buf(line, tmp);
			line[str_len(line)] = '\0';
			add_buf(line, spread);
			extended = 1;
		}
		break;
		m++;
	}
	if (extended)
	{
		free(data->new_line);
		data->new_line = str_dupl(line);
	}
}

/**
 * add_buf - end of  buffer.
 *
 * @buff: buffer.
 * @string_add: copied buffer.
 * Return: nothing.
 */
int add_buf(char *buff, char *string_add)
{
	int len, m = 0;

	len = str_len(buff);
	while (string_add[m])
	{
		buff[len + m] = string_add[m];
		m++;
	}
	buff[len + m] = '\0';
	return (len + m);
}
