#include "aushell.h"

int my_cd(char **argv, char **node);

/**
 * get_builtin - Function to correspond with a builtin command
 *					in AUshell.
 * @cmd: variable for corresponding builtin command.
 *
 * Return: corresponding command.
 */
int (*get_builtin(char *cmd))(char **argv, char **node)
{
	builtin_t table[] = {
		{ "exit", my_exit },
		{ "env", my_env },
		{ "setenv", my_setenv },
		{ "unsetenv", my_unsetenv },
		{ "cd", my_cd },
		{ "alias", my_alias },
		{ "help", my_help },
		{ NULL, NULL }
	};
	int index;

	for (index = 0; table[index].name; index++)
	{
		if (str_cmp(table[index].name, cmd) == 0)
			break;
	}
	return (table[index].func);
}

/**
 * my_exit - Function to exit from shell by returning various exit status
 * @argv: Argument Vector
 * @node: A pointer to the beginning of arguments vector.
 *
 * Return: The various exit status of the shell
 *
 */
int my_exit(char **argv, char **node)
{
	int i;
	int int_length = 10; /* Maximum length of integer */
	unsigned int string_value = 0; /* Value of string */
	unsigned int max = 1 << (sizeof(int) * 8 - 1); /*Maximum integer value*/

	(void) node;

		/* Check if argument is provided */
	if (argv[0])
	{
		/* Check if the string starts with a '+' sign */
		if (argv[0][0] == '+')
		{
			i = 1;
			int_length++; /* Increase the length of the integer string */
		}

		/* Parse the string to an integer */
		while (argv[0][i] && i <= int_length && argv[0][i] >= '0'
				&& argv[0][i] <= '9')
		{
			string_value = (string_value * 10) + (argv[0][i] - '0');
			i++;
		}

		/* Check if the string contains invalid characters */
		if (argv[0][i] != '\0')
			return (make_errors(--argv, 2));
	}
	else /* No argument provided */
	{
		return (-3);
	}

	/* Check if the integer value is within the maximum range */
	if (string_value > max - 1)
		return (make_errors(--argv, 2));

	argv -= 1; /* Decrement the argument pointer */
	free_args(argv, node); /* Free the memory allocated for arguments */
	free_env(); /* Free the environment variable list */
	free_alias_node(myalias); /* Free the alias list */
	exit(string_value); /* Exit with the integer value */
}

/**
 * my_cd - Function to change the current working directory.
 * @argv: Null-terminated array of arguments passed to the shell.
 * @node: Unused array of strings that represents the shell's history.
 *
 * Return: 0 on success, or a negative number on failure.
 */
int my_cd(char **argv, char **node)
{
	char **dir_info, *new_line = "\n";
	char *old_pwd = NULL, *curr_pwd = NULL;
	struct stat dir;

	(void) node;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	switch (argv[0] ? argv[0][0] : '\0')
	{
		case '-':
			if (argv[0][1] != '\0')
				return (make_errors(argv, 2));
			if (my_getenv("OLDPWD") == NULL)
				return (make_errors(argv, 2));
			chdir(*my_getenv("OLDPWD") + 7);
			break;
		case '\0':
			if (my_getenv("HOME") == NULL)
				return (make_errors(argv, 2));
			chdir(*(my_getenv("HOME")) + 5);
			break;
		default:
			if (stat(argv[0], &dir) == 0 && S_ISDIR(dir.st_mode)
				&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(argv[0]);
			else
				return (make_errors(argv, 2));
			break;
	}

	curr_pwd = getcwd(curr_pwd, 0);
	if (!curr_pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = old_pwd;
	if (my_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = curr_pwd;
	if (my_setenv(dir_info, dir_info) == -1)
		return (-1);

	if (argv[0] && argv[0][0] == '-' && argv[0][1] != '-')
	{
		write(STDOUT_FILENO, curr_pwd, str_len(curr_pwd));
		write(STDOUT_FILENO, new_line, 1);
	}

	free(old_pwd);
	free(curr_pwd);
	free(dir_info);

	return (0);
}



/**
 * my_help - Displays information about shellby builtin commands.
 * @argv: An array of arguments.
 * @node: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_help(char **argv, char **node)
{
	(void) node;

	if (!argv[0])
		all_help();
	else if (str_cmp(argv[0], "cd") == 0)
		cd_help();

	else if (str_cmp(argv[0], "env") == 0)
		env_help();

	else if (str_cmp(argv[0], "setenv") == 0)
		setenv_help();

	else if (str_cmp(argv[0], "unsetenv") == 0)
		unsetenv_help();

	else if (str_cmp(argv[0], "exit") == 0)
		exit_help();

	else if (str_cmp(argv[0], "alias") == 0)
		alias_help();

	else if (str_cmp(argv[0], "help") == 0)
		helps_help();
	else
		write(STDERR_FILENO, command_name, str_len(command_name));

	return (0);
}


