#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	program_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void inicialize_data(program_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->new_line = NULL;
	data->cmd_name = NULL;
	data->run_count = 0;
	/* define the file descriptor to be readed*/
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
		for (; env[i]; i++)
		{
			data->env[i] = str_dupl(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->list[i] = NULL;
	}
}
/**
 * sisifo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void sisifo(char *prompt, program_data *data)
{
	int code_err = 0, string_len = 0;

	while (++(data->run_count))
	{
		_print(prompt);
		code_err = string_len = _getline(data);

		if (code_err == EOF)
		{
			free_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			extend_alias(data);
			extend_var(data);
			symbolize(data);
			if (data->symbols[0])
			{ /* if a text is given to prompt, run */
				code_err = run(data);
				if (code_err != 0)
					_print_err(code_err, data);
			}
			free_Periodic(data);
		}
	}
}
