#include "shell.h"
/**
 * internal_list - search and run.
 * @data: program's data.
 * Return: function executed.
 **/
int internal_list(program_data *data)
{

	int navigator;
	internals alter[] = {
		{"exit", shell_exit},
		{"help", shell_help},
		{"cd", shell_cd},
		{"alias", alias_shell},
		{"env", internal_env},
		{"setenv", internal_env_set},
		{"unsetenv", internal_env_clear},
		{NULL, NULL}
	};

	for (navigator = 0; alter[navigator].builtin != NULL; navigator++)
	{

		if (str_cmp(alter[navigator].builtin, data->cmd_name, 0))
		{
			return (alter[navigator].function(data));
		}
	}
	return (-1);
}
