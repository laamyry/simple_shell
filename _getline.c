#include "shell.h"
/**
* _getline - get line.
* @data: program's data.
*
* Return: count bytes.
*/
int _getline(program_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *cmd_array[10] = {NULL};
	static char operas_array[10] = {'\0'};
	ssize_t read_byte, m = 0;

	if (!cmd_array[0] || (operas_array[0] == '&' && errno != 0) ||
		(operas_array[0] == '|' && errno == 0))
	{
		while (cmd_array[m])
		{
			free(cmd_array[m]);
			cmd_array[m] = NULL;
			m++;
		}

		read_byte = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (read_byte == 0)
			return (-1);

		m = 0;
		do {
			cmd_array[m] = str_dupl(_strtok(m ? NULL : buff, "\n;"));
			m = check_operas(cmd_array, m, operas_array);
		} while (cmd_array[m++]);
	}

	data->new_line = cmd_array[0];
	for (m = 0; cmd_array[m]; m++)
	{
		cmd_array[m] = cmd_array[m + 1];
		operas_array[m] = operas_array[m + 1];
	}
	return (str_len(data->new_line));
}

/**
* check_operas - operators checker.
*
* @cmd_array: array.
* @m: index.
* @operas_array: array.
* Return: index .
*/
int check_operas(char *cmd_array[], int m, char operas_array[])
{
	char *tmp = NULL;
	int n;

	for (n = 0; cmd_array[m] != NULL  && cmd_array[m][n]; n++)
	{
		if (cmd_array[m][n] == '&' && cmd_array[m][n + 1] == '&')
		{
			tmp = cmd_array[m];
			cmd_array[m][n] = '\0';
			cmd_array[m] = str_dupl(cmd_array[m]);
			cmd_array[m + 1] = str_dupl(tmp + n + 2);
			m++;
			operas_array[m] = '&';
			free(tmp);
			n = 0;
		}
		if (cmd_array[m][n] == '|' && cmd_array[m][n + 1] == '|')
		{
			tmp = cmd_array[m];
			cmd_array[m][n] = '\0';
			cmd_array[m] = str_dupl(cmd_array[m]);
			cmd_array[m + 1] = str_dupl(tmp + n + 2);
			m++;
			operas_array[m] = '|';
			free(tmp);
			n = 0;
		}
	}
	return (m);
}
