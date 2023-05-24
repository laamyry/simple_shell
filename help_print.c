#include "shell.h"
/**
 * _print - print array.
 *
 * @string: pointer.
 * Return: byte's number .
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_len(string)));
}
/**
 * _printf - print array.
 *
 * @string: pointer.
 * Return: byte's number.
 */
int _printf(char *string)
{
	return (write(STDERR_FILENO, string, str_len(string)));
}

/**
 * _print_err - print array.
 *
 * @data: program's data pointer.
 * @error_c: error code.
 * Return: byte's number.
 */
int _print_err(int error_c, program_data *data)
{
	char nu_string[10] = {'\0'};

	long_str((long) data->run_count, nu_string, 10);

	if (error_c == 2 || error_c == 3)
	{
		_printf(data->program_name);
		_printf(": ");
		_printf(nu_string);
		_printf(": ");
		_printf(data->symbols[0]);
		if (error_c == 2)
			_printf(": Illegal number: ");
		else
			_printf(": can't cd to ");
		_printf(data->symbols[1]);
		_printf("\n");
	}
	else if (error_c == 127)
	{
		_printf(data->program_name);
		_printf(": ");
		_printf(nu_string);
		_printf(": ");
		_printf(data->cmd_name);
		_printf(": not found\n");
	}
	else if (error_c == 126)
	{
		_printf(data->program_name);
		_printf(": ");
		_printf(nu_string);
		_printf(": ");
		_printf(data->cmd_name);
		_printf(": Permission denied\n");
	}
	return (0);
}
