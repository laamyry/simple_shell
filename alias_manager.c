#include "shell.h"
/**
 * p_alias - add, delet and display aliases.
 * @data: program's data.
 * @alias: printed alias.
 * Return: 0 sucess, or argument number.
 */
int p_alias(program_data *data, char *alias)
{

	int m = 0, n, len;
	char buff[250] = {'\0'};

	if (data->list)
	{
		len = str_len(alias);

		while (data->list[m])
		{
			if (!alias || (str_cmp(data->list[m], alias, len) &&
			data->list[m][len] == '='))
		{
		for (n = 0; data->list[m][n]; n++)
		{
   			buff[n] = data->list[m][n];
   			if (data->list[m][n] == '=')
			break;
		}
		buff[n + 1] = '\0';
		add_buf(buff, "'");
		add_buf(buff, data->list[m] + n + 1);
		add_buf(buff, "'\n");
		_print(buff);
	}
	m++;
}
	}

	return (0);

}

/**
 * obt_alias - add, delet and display aliases.
 * @data: program's data.
 * @name: name of printed alias.
 * Return: 0 sucess, or argument number.
 */
char *obt_alias(program_data *data, char *name)
{
	int m = 0, len;

	if (name == NULL || data->list == NULL)
	{
		return (NULL);
	}

	len = str_len(name);

	while (data->list[m])
	{
		if (str_cmp(name, data->list[m], len) &&
			data->list[m][len] == '=')
		{
			return (data->list[m] + len + 1);
		}
		m++;
	}
	return (NULL);

}

/**
 * esta_alias - add alias.
 * @alias_str: alias string.
 * @data: the program's data.
 * Return: 0 sucess, or argument number.
 */
int esta_alias(char *alias_str, program_data *data)
{

	int m = 0, n = 0;
	char buff[250] = {'0'}, *tmp = NULL;

	if (alias_str == NULL ||  data->list == NULL)
	{
		return (1);
	}
	while (alias_str[m])
	{
		if (alias_str[m] != '=')
		{
			buff[m] = alias_str[m];
		}
		else
		{
			tmp = obt_alias(data, alias_str + m + 1);
			break;
		}
		m++;
	}

	while (data->list[n])
	{
		if (str_cmp(buff, data->list[n], m) &&
			data->list[n][m] == '=')
		{
			free(data->list[n]);
			break;
		}
		n++;
	}

	if (tmp)
	{
		add_buf(buff, "=");
		add_buf(buff, tmp);
		data->list[n] = str_dupl(buff);
	}
	else
	{
		data->list[n] = str_dupl(alias_str);
	}
	return (0);

}
