#include "shell.h"
/**
 * internal_env - display the environment runs
 * @data: program's data
 * Return: 0 sucess, or argument number.
 */
int internal_env(program_data *data)
{

	int m = 0;
	char cp_n[50] = {'\0'};
	char *vari_cp = NULL;

	if (data->symbols[1] == NULL)
	{
		print_env(data);
	}

	else
	{
		while (data->symbols[1][m])
		{
			if (data->symbols[1][m] == '=')
			{
				vari_cp = str_dupl(env_key(cp_n, data));
				if (vari_cp != NULL)
				{
					env_key_set(cp_n, data->symbols[1] + m + 1, data);
				}

				print_env(data);
				if (env_key(cp_n, data) == NULL)
				{
					_print(data->symbols[1]);
					_print("\n");
				}
				else
				{
					env_key_set(cp_n, vari_cp, data);
					free(vari_cp);
				}
				return (0);
			}
			cp_n[m] = data->symbols[1][m];
			m++;
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * internal_env_set - set the environment.
 * @data: program's data.
 * Return: 0 sucess, or argument number.
 */
int internal_env_set(program_data *data)
{

	if (data->symbols[1] == NULL || data->symbols[2] == NULL)
	{
		return (0);
	}
	if (data->symbols[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	env_key_set(data->symbols[1], data->symbols[2], data);
	return (0);
}

/**
 * internal_env_clear - clear the environment.
 * @data: program's data.
 * Return: 0 sucess, or argument number.
 */
int internal_env_clear(program_data *data)
{

	if (data->symbols[1] == NULL)
	{
		return (0);
	}
	if (data->symbols[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	env_remove_key(data->symbols[1], data);
	return (0);

}
