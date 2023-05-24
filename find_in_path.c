#include "shell.h"

int check_file(char *full_path);

/**
 * locat_prog - find a program in path
 * @data: program's data pointer
 * Return: 0 if success, errcode otherwise
 */

int locat_prog(program_data *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->cmd_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (check_file(data->cmd_name));

	free(data->symbols[0]);
	data->symbols[0] = str_join(str_dupl("/"), data->cmd_name);
	if (!data->symbols[0])
		return (2);

	directories = tokenize_path(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{/* appends the function_name to path */
		directories[i] = str_join(directories[i], data->symbols[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has run permisions*/
			errno = 0;
			free(data->symbols[0]);
			data->symbols[0] = str_dupl(directories[i]);
			arr_free(directories);
			return (ret_code);
		}
	}
	free(data->symbols[0]);
	data->symbols[0] = NULL;
	arr_free(directories);
	return (ret_code);
}

/**
 * tokenize_path - symbolize the path in directories
 * @data: program's data pointer
 * Return: array of path directories
 */

char **tokenize_path(program_data *data)
{
	int i = 0;
	int counter_directories = 2;
	char **symbols = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_dupl(PATH);

	/* find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	/* reserve space for the array of pointers */
	symbols = malloc(sizeof(char *) * counter_directories);

	/*symbolize and duplicate each token of path*/
	i = 0;
	symbols[i] = str_dupl(_strtok(PATH, ":"));
	while (symbols[i++])
	{
		symbols[i] = str_dupl(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (symbols);

}

/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
