#include "aushell.h"

int file_pro_cmd(char *file_path, int *exit_code);

/**
 * file_pro_cmd - Function to takes a run file command.
 * @file_path: Variable for file's path.
 * @exit_code: variable for returned exit code.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int file_pro_cmd(char *file_path, int *exit_code)
{
	ssize_t file, bytes_read, index;
	unsigned int line_val = 0, old_val = 120;
	char *file_line, **args, **fword;
	char buf[120];
	int ret;

	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exit_code = disply_open_error(file_path);
		return (*exit_code);
	}

	file_line = malloc(sizeof(char) * old_val);
	if (!file_line)
		return (-1);

	do {
		bytes_read = read(file, buf, 119);
		if (bytes_read == 0 && line_val == 0)
			return (*exit_code);
		buf[bytes_read] = '\0';

		line_val += bytes_read;
		file_line = my_realloc(file_line, old_val, line_val);
		str_cat(file_line, buf);
		old_val = line_val;
	} while (bytes_read);

	for (index = 0; file_line[index] == '\n'; index++)
		file_line[index] = ' ';

	for (; index < line_val; index++)
	{
		if (file_line[index] == '\n')
		{
			file_line[index] = ';';
			for (index += 1; index < line_val && file_line[index] == '\n'; index++)
				file_line[index] = ' ';
		}
	}

	replace_var(&file_line, exit_code);
	check_line(&file_line, line_val);

	args = my_strtok(file_line, " ");
	free(file_line);
	if (!args)
		return (0);

	if (verify_args(args) != 0)
	{
		*exit_code = 2;
		free_args(args, args);
		return (*exit_code);
	}

	fword = args;
	for (index = 0; args[index]; index++)
	{
		if (strn_cmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, fword, exit_code);
			args = &args[++index];
			index = 0;
		}
	}

	ret = call_args(args, fword, exit_code);
	free(fword);
	return (ret);
}



/**
 * disply_open_error - Function prints a error message for a file manipulation.
 * @file_path: The path to the file that can't be opened.
 *
 * Return: integer type.
 */
int disply_open_error(char *file_path)
{
	char *error_msg, *str;
	int error_len;

	str = my_itoa(history);
	if (!str)
		return (127);

	error_len = str_len(command_name) + str_len(str) + str_len(file_path) + 16;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(str);
		return (127);
	}

	str_cpy(error_msg, command_name);
	str_cat(error_msg, ": ");
	str_cat(error_msg, str);
	str_cat(error_msg, ": File cannot be opened");
	str_cat(error_msg, file_path);
	str_cat(error_msg, "\n");

	free(str);

	write(STDERR_FILENO, error_msg, error_len);

	free(error_msg);

	return (127);
}

