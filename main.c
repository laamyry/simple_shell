#include "shell.h"
/**
 * main - Initialize program variables.
 * 
 * @argc: Command line input count.
 * @argv: Command line input values
 * @env: Command line input count.
 * Return: 0 = succes.
 */
int main(int argc, char *argv[], char *env[])
{
	program_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, ctrl_c_handle);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	pro_inf(prompt, data);
	return (0);
}

/**
 * ctrl_c_handle - When the program receives the SIGINT
 * (Ctrl + C) signal, print the prompt on a new line.
 * 
 * @UNUSED: option of the prototype
 */
void ctrl_c_handle(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - Initialize the struct with program information.
 * 
 * @data: data structure pointer.
 * @argv: Program execution arguments array.
 * @env: Environment passed during program execution.
 * @argc: Count of command line input values.
 */
void initialize_data(program_data *data, int argc, char *argv[], char **env)
{
	int m = 0;

	data->program_name = argv[0];
	data->new_line = NULL;
	data->cmd_name = NULL;
	data->run_count = 0;

	if (argc == 1)
		data->file_identifier = STDIN_FILENO;
	else
	{
		data->file_identifier = open(argv[1], O_RDONLY);
		if (data->file_identifier == -1)
		{
			_printf(data->program_name);
			_printf(": 0: Can't open ");
			_printf(argv[1]);
			_printf("\n");
			exit(127);
		}
	}
	data->symbols = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[m]; m++)
		{
			data->env[m] = str_dupl(env[m]);
		}
	}
	data->env[m] = NULL;
	env = data->env;

	data->list = malloc(sizeof(char *) * 20);
	for (m = 0; m < 20; m++)
	{
		data->list[m] = NULL;
	}
}
/**
 * pro_inf - It's an endless loop displaying the prompt.
 * 
 * @prompt: Print Prompt.
 * @data: It's an endless loop displaying the prompt.
 */
void pro_inf(char *prompt, program_data *data)
{
	int code_err = 0, string_len = 0;

	while (++(data->run_count))
	{
		_print(prompt);
		code_err = string_len = _getline(data);

		if (code_err == EOF)
		{
			free_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			extend_alias(data);
			extend_var(data);
			symbolize(data);
			if (data->symbols[0])
			{
				code_err = run(data);
				if (code_err != 0)
					_print_err(code_err, data);
			}
			free_Periodic(data);
		}
	}
}
