#include "shell.h"
/**
 * env_key - find environment variable.
 * @key: environment variable.
 * @data: program's data.
 * Return: a pointer.
 */
char *env_key(char *key, program_data *data)
{
	int m = 0, len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);
	len = str_len(key);

	while (data->env[m])
	{
		if (str_cmp(key, data->env[m], len) &&
		 data->env[m][len] == '=')
		{
			return (data->env[m] + len + 1);
		}
		m++;
	}
	return (NULL);
}

/**
 * env_key_set - overwrit or add.
 *
 * @key: variable name.
 * @value: new value.
 * @data: program's data.
 * Return: 1 =  NULL, 2 = error 0 = sucess.
 */

int env_key_set(char *key, char *value, program_data *data)
{
	int m = 0, len = 0, new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	len = str_len(key);

	while (data->env[m])
	{
		if (str_cmp(key, data->env[m], len) &&
		 data->env[m][len] == '=')
		{
			new_key = 0;
			free(data->env[m]);
			break;
		}
		m++;
	}
	data->env[m] = str_join(str_dupl(key), "=");
	data->env[m] = str_join(data->env[m], value);
	if (new_key)
	{
		data->env[m + 1] = NULL;
	}
	return (0);
}

/**
 * delete_env_key - delete the environment key.
 *
 * @key: key be delete.
 * @data: program's data.
 * Return: 1 = deleted, 0 = not exist.
 */
int delete_env_key(char *key, program_data *data)
{
	int m = 0, len = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	len = str_len(key);
	while (data->env[m])
	{
		if (str_cmp(key, data->env[m], len) &&
		 data->env[m][len] == '=')
		{
			free(data->env[m]);

			m++;
			for (; data->env[m]; m++)
			{
				data->env[m - 1] = data->env[m];
			}
			data->env[m - 1] = NULL;
			return (1);
		}
		m++;
	}
	return (0);
}

/**
 * print_env - print the environment.
 *
 * @data: program's data.
 * Return: nothing.
 */
void print_env(program_data *data)
{
	int n = 0;

	while (data->env[n])
	{
		_print(data->env[n]);
		_print("\n");
		n++;
	}
}
