#include "shell.h"

/**
 * free_Periodic - free.
 *
 * @data: program's data.
 * Return: Nothing.
 */
void free_Periodic(program_data *data)
{
	if (data->symbols)
		arr_free(data->symbols);
	if (data->new_line)
		free(data->new_line);
	if (data->cmd_name)
		free(data->cmd_name);

	data->new_line = NULL;
	data->cmd_name = NULL;
	data->symbols = NULL;
}

/**
 * free_data - free data.
 *
 * @data: program's data.
 * Return: Nothing.
 */
void free_data(program_data *data)
{
	if (data->file_identifier != 0)
	{
		if (close(data->file_identifier))
			perror(data->program_name);
	}
	free_Periodic(data);
	arr_free(data->env);
	arr_free(data->list);
}

/**
 * arr_free - frees array.
 *
 * @array: pointer's array.
 * Return: nothing.
 */
void arr_free(char **array)
{
	int m = 0;

	if (array != NULL)
	{
		while (array[m])
		{
			free(array[m]);
			 m++;
		}

		free(array);
		array = NULL;
	}
}
