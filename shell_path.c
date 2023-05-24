#include "aushell.h"

char *fill_path_buf(char *path_tokens);

/**
 * fill_path_buf - Function for path buffer.
 * @path_tokens: Variable for dicretorie that needs to be found.
 *
 * Return: A copy of path for current working directory.
 */
char *fill_path_buf(char *path_tokens)
{
	int i, length = 0;
	char *buffer, *current_dir;

	current_dir = *(my_getenv("PWD")) + 4;
	for (i = 0; path_tokens[i]; i++)
	{
		if (path_tokens[i] == ':')
		{
			if (path_tokens[i + 1] == ':' || i == 0 || path_tokens[i + 1] == '\0')
				length += str_len(current_dir) + 1;
			else
				length++;
		}
		else
			length++;
	}
	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	for (i = 0; path_tokens[i]; i++)
	{
		if (path_tokens[i] == ':')
		{
			if (i == 0)
			{
				str_cat(buffer, current_dir);
				str_cat(buffer, ":");
			}
			else if (path_tokens[i + 1] == ':' || path_tokens[i + 1] == '\0')
			{
				str_cat(buffer, ":");
				str_cat(buffer, current_dir);
			}
			else
				str_cat(buffer, ":");
		}
		else
		{
			strn_cat(buffer, &path_tokens[i], 1);
		}
	}
	return (buffer);
}

/**
 * get_path - Function to get the directory path.
 * @env_name: Variable for directories.
 *
 * Return: Path for the list.
 */
list_t *get_path(char *env_name)
{
	int env_index;
	char **token_path, *env_value;
	list_t *path_head = NULL;

	env_value = fill_path_buf(env_name);
	if (!env_value)
		return (NULL);
	token_path = my_strtok(env_value, ":");
	free(env_value);
	if (!token_path)
		return (NULL);

	for (env_index = 0; token_path[env_index]; env_index++)
	{
		if (add_node_end(&path_head, token_path[env_index]) == NULL)
		{
			free_node(path_head);
			free(token_path);
			return (NULL);
		}
	}

	free(token_path);

	return (path_head);
}


/**
 * find_executable_path - Function the path of execution for the program
 * @command: Represents a command.
 * Return: On sucess, a string with the full path of the program.
 *                                 Otherwise returns NULL.
 */
char *find_executable_path(char *command)
{
	char **path_tokens, *path;
	list_t *executable_path, *dir_head;
	struct stat stat_buffer;

	path_tokens = my_getenv("PATH");
	if (!path_tokens || !(*path_tokens))
		return (NULL);

	executable_path = get_path(*path_tokens + 5);
	dir_head = executable_path;

	while (executable_path)
	{
		path = malloc(str_len(executable_path->dir) + str_len(command) + 2);
		if (!path)
			return (NULL);

		str_cpy(path, executable_path->dir);
		str_cat(path, "/");
		str_cat(path, command);

		if (stat(path, &stat_buffer) == 0)
		{
			free_node(dir_head);
			return (path);
		}

		executable_path = executable_path->next;
		free(path);
	}

	free_node(dir_head);
	return (NULL);
}
