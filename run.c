#include "shell.h"
/**
 * run - run command.
 *
 * @data: program's data pointer
 * Return: sucess = zero, else = -1.
 */
int run(program_data *data)
{
	int m = 0, status;
	pid_t pidd;

	m = internal_list(data);
	if (m != -1)
		return (m);
	m = locat_prog(data);
	if (m)
	{
		return (m);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			m = execve(data->symbols[0], data->symbols, data->env);
			if (m == -1)
				perror(data->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
