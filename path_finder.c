#include "shell.h"
/**
 * locat_prog - find program.
 *
 * @data: program's data pointer.
 * Return: 0 if success.
 */

int locat_prog(program_data *data)
{
	int m = 0, ret_code = 0;
	char **directs;

	if (!data->cmd_name)
		return (2);

	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (file_chekcer(data->cmd_name));

	free(data->symbols[0]);
	data->symbols[0] = str_join(str_dupl("/"), data->cmd_name);
	if (!data->symbols[0])
		return (2);

	directs = symbolize_path(data);

	if (!directs || !directs[0])
	{
		errno = 127;
		return (127);
	}
	while (directs[m])
	{
		directs[m] = str_join(directs[m], data->symbols[0]);
		ret_code = file_chekcer(directs[m]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->symbols[0]);
			data->symbols[0] = str_dupl(directs[m]);
			arr_free(directs);
			return (ret_code);
		}
		m++;
	}
	free(data->symbols[0]);
	data->symbols[0] = NULL;
	arr_free(directs);
	return (ret_code);
}

/**
 * symbolize_path - symbolize the path.
 *
 * @data: program's data pointer.
 * Return: array.
 */

char **symbolize_path(program_data *data)
{
	int m = 0;
	int directs_counter = 2;
	char **symbols = NULL;
	char *PATH;

	PATH = env_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_dupl(PATH);

	while (PATH[m])
	{
		if (PATH[m] == ':')
		{
			directs_counter++;
		}
		m++;
	}

	symbols = malloc(sizeof(char *) * directs_counter);

	m = 0;
	symbols[m] = str_dupl(_strtok(PATH, ":"));
	while (symbols[m++])
	{
		symbols[m] = str_dupl(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (symbols);

}

/**
 * file_chekcer - checks if exists.
 *
 * @full_path: pointer.
 * Return: 0 on success.
 */

int file_chekcer(char *full_path)
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
	errno = 127;
	return (127);
}
