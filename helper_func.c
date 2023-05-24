#include "aushell.h"

void replace_var(char **line, int *exec_ret);

/**
 * my_getpid - Function to get the current process ID.
 *
 * Return: Character type.
 */
char *my_getpid(void)
{
	size_t index = 0;
	char *temp;
	ssize_t file_name;

	file_name = open("/proc/self/stat", O_RDONLY);
	if (file_name == -1) /* Check if the file opened successfully */
	{
		perror("Can not read this file"); /* Print an error message */
		return (NULL); /* Return NULL to indicate failure */
	}

	temp = malloc(120); /* Allocate a buffer to store the PID */
	if (!temp) /* Check if the buffer allocation was successful */
	{
		close(file_name); /* Close the file */
		return (NULL); /* Return NULL to indicate failure */
	}

	read(file_name, temp, 120); /* Read the contents of the file*/
	while (temp[index] != ' ') /* Find the space */
		index++;
	temp[index] = '\0'; /* Replace the space */

	close(file_name); /* Close the file */
	return (temp); /* Return the PID as a string */
}

/**
 * replace_var - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exec_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void replace_var(char **line, int *exec_ret)
{
	int num, i = 0, len;
	char *replace = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (num = 0; old_line[num]; num++)
	{
		if (old_line[num] == '$' && old_line[num + 1] &&
				old_line[num + 1] != ' ')
		{
			if (old_line[num + 1] == '$')
			{
				replace = my_getpid();
				i = num + 2;
			}
			else if (old_line[num + 1] == '?')
			{
				replace = my_itoa(*exec_ret);
				i = num + 2;
			}
			else if (old_line[num + 1])
			{
				/* extract the variable name to search for */
				for (i = num + 1; old_line[i] &&
						old_line[i] != '$' &&
						old_line[i] != ' '; i++)
					;
				len = i - (num + 1);
				replace = get_env_var(&old_line[num + 1], len);
			}
			new_line = malloc(num + str_len(replace)
					  + str_len(&old_line[i]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			strn_cat(new_line, old_line, num);
			if (replace)
			{
				str_cat(new_line, replace);
				free(replace);
				replace = NULL;
			}
			str_cat(new_line, &old_line[i]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			num = -1;
		}
	}
}

/**
 * get_env_var - function to get environment variable.
 *
 * @start: variable for start of the environment variable name.
 * @length: variable for length of the environment variable name.
 *
 * Return:
 * - On success, a pointer to a newly allocated string
 *	containing the value of the environment variable.
 * - On failure, NULL.
 */
char *get_env_var(char *start, int length)
{
	char **var_add;
	char *replace = NULL;
	char *buffer, *var_name;

	/* Allocate memory for the variable */
	var_name = malloc(length + 1);
	if (!var_name)
		return (NULL);
	var_name[0] = '\0';
	strn_cat(var_name, start, length);

	/* Get the address of the environment variable */
	var_add = my_getenv(var_name);
	free(var_name);

	/* If the variable is found, extract its value and return it */
	if (var_add)
	{
		buffer = *var_add;
		while (*buffer != '=')
			buffer++;
		buffer++;
		replace = malloc(str_len(buffer) + 1);
		if (replace)
			str_cpy(replace, buffer);
	}

	return (replace);
}

/**
 * free_args - Function to free memory taken.
 * @argv: variable for arguments array.
 * @node: variable for arguments first node.
 */
void free_args(char **argv, char **node)
{
	size_t index;

	while (argv[index] || argv[index + 1]) /* While condition*/
	{
		free(argv[index]); /* Free the memory allocated */
		index++; /* Increment the counter variable 'i' */
	}

	free(node); /* Free the memory allocated */
}

