#include "shell.h"
/**
 * shell_exit - program's exit.
 * @data: program's data
 * Return: 0 sucess, or argument number.
 */
int shell_exit(program_data *data)
{
	int m = 0;

	if (data->symbols[1] != NULL)
	{
		while (data->symbols[1][m])
		{
			if ((data->symbols[1][m] < '0' || data->symbols[1][m] > '9')
					&& data->symbols[1][m] != '+')
			{
				errno = 2;
				return (2);
			}
			m++;
		}
		errno = _atoi(data->symbols[1]);
	}
	data_free(data);
	exit(errno);
}

/**
 * shell_cd - change directory.
 *
 * @data: program's data.
 * Return: 0 sucess, or argument number.
 */
int shell_cd(program_data *data)
{
	int code_err = 0;
	char *home_d = env_key("HOME", data), *old_d = NULL;
	char old_direc[128] = {0};


	if (data->symbols[1])
	{
		if (str_cmp(data->symbols[1], "-", 0))
		{
			old_d = env_key("OLDPWD", data);
			if (old_d)
			{
				code_err = work_d_set(data, old_d);
			}
			_print(env_key("PWD", data));
			_print("\n");

			return (code_err);
		}
		else
		{
			return (work_d_set(data, data->symbols[1]));
		}
	}
	else
	{
		if (!home_d)
			home_d = getcwd(old_direc, 128);

		return (work_d_set(data, home_d));
	}
	return (0);
}

/**
 * work_d_set - work directory.
 *
 * @data: program's data.
 * @new_d: work directory.
 * Return: 0 sucess, or argument number.
 */
int work_d_set(program_data *data, char *new_d)
{
	char old_direc[128] = {0};
	int err_code = 0;

	getcwd(old_direc, 128);

	if (!str_cmp(old_direc, new_d, 0))
	{
		err_code = chdir(new_d);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_key_set("PWD", new_d, data);
	}
	env_key_set("OLDPWD", old_direc, data);
	return (0);
}

/**
 * shell_help - show shell help.
 * @data: program's data.
 * Return: 0 sucess, or argument number.
 */
int shell_help(program_data *data)
{

	int m, len = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	if (data->symbols[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (data->symbols[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (m = 0; messages[m]; m++)
	{
		len = str_len(data->symbols[1]);
		if (str_cmp(data->symbols[1], messages[m], len))
		{
			_print(messages[m] + len + 1);
			return (1);
		}
	}

	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * alias_shell - add/delete/display aliases
 * @data: program's data.
 * Return: 0 sucess, or argument number.
 */
int alias_shell(program_data *data)
{
	int m = 0;

	if (data->symbols[1] == NULL)
	{
		return (p_alias(data, NULL));
	}

	while (data->symbols[++m])
	{
		if (char_counter(data->symbols[m], "="))
		{
			esta_alias(data->symbols[m], data);
		}
		else
		{
			p_alias(data, data->symbols[m]);
		}
	}

	return (0);
}
