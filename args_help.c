#include "aushell.h"

int call_args(char **argv, char **node, int *exec_ret);


/**
 * call_args -  function to call arguments.
 * @argv: variable for arguments array.
 * @node: variable for first node.
 * @exec_ret: variable to execute return.
 *
 * Return: integer type.
 */
int call_args(char **argv, char **node, int *exec_ret)
{
	int exit_code, i = 0;

	if (!argv[0])
		return (*exec_ret);

	while (argv[i])
	{
		/* Check for || conditions*/
		if (strn_cmp(argv[i], "||", 2) == 0)
		{
			free(argv[i]);
			argv[i] = NULL;
			argv = replace_alias(argv);
			exit_code = exec_args(argv, node, exec_ret);

			/* Check if the previous command failed */
			if (*exec_ret != 0)
			{
				argv = &argv[++i];
				i = 0;/* Reset index to restart from the begining*/
			}
			else
			{
				/* Free the arguments left and return the equivalent result*/
				for (i++; argv[i]; i++)
					free(argv[i]);
				return (exit_code);
			}
		}
		/*Check for && condition */
		else if (strn_cmp(argv[i], "&&", 2) == 0)
		{
			free(argv[i]);
			argv[i] = NULL;
			argv = replace_alias(argv);
			exit_code = exec_args(argv, node, exec_ret);

			/*Check if previous command was successful*/
			if (*exec_ret == 0)
			{
				argv = &argv[++i];
				i = 0; /* Reset index to restart from the begining*/
			}
			else
			{
				/*Free arguments left and return equivalent result*/
				for (i++; argv[i]; i++)
					free(argv[i]);
				return (exit_code);
			}
		}

		i++;
	}

	/*change alias, execute the command and return the result*/
	argv = replace_alias(argv);
	exit_code = exec_args(argv, node, exec_ret);
	return (exit_code);
}

/**
 * read_args - Function to reads a line.
 * @input: varible for input command.
 * @exec_ret: variable for execution return.
 *
 * Return: Pointer to the modified line.
 */
char *read_args(char *input, int *exec_ret)
{
	char *shell_prompt = HOME;
	ssize_t read;
	size_t num = 0;

	/* Free the previously allocated line */
	if (input)
		free(input);

	/*Read a line from the STDIN*/
	read = my_getline(&input, &num, STDIN_FILENO);
	if (read == -1)
		return (NULL);

	/*Prompt User for input if a new line is entered*/
	if (read == 1)
	{
		history++;
		/*Display Prompt to allow interactive mode*/
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, shell_prompt, str_len(shell_prompt));
		return (read_args(input, exec_ret));
	}

	/*Replace the Newline character to perform Null-terminate*/
	input[read - 1] = '\0';
	replace_var(&input, exec_ret);/* Perform variable replacement */
	check_line(&input, read);/*Perform handle line operation*/

	return (input);
}

/**
 * exec_args - Function to exectute command.
 * @argv: Variable for argument array.
 * @node: variable for pointer to the node.
 * @exec_ret: variable for execution return value.
 *
 * Return: integer type.
 */
int exec_args(char **argv, char **node, int *exec_ret)
{
	int exit_code;
	int i = 0;
	int (*builtin)(char **argv, char **node);

	/* Get the corresponding builtin function for the command */
	builtin = get_builtin(argv[0]);

	if (builtin)
	{
		/* Execute the builtin function */
		exit_code = builtin(argv + 1, node);

		/* Update the execution return value if necessary */
		if (exit_code != EXIT)
			*exec_ret = exit_code;
	}
	else
	{
		/* Execute the command and update the execution return value */
		*exec_ret = shell_run(argv, node);
		exit_code = *exec_ret;
	}

	history++;

	/* Free the allocated command arguments */
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}

	return (exit_code);
}

/**
 * verify_args - Function to verifies argument for special symbols.
 * @argv: variable for argument array.
 *
 * Return: integer type.
 */
int verify_args(char **argv)
{
	char *curr_val, *next_val;
	size_t index;


	for (index = 0; argv[index]; index++)
	{
		curr_val = argv[index];
		if (curr_val[0] == ';' || curr_val[0] == '&' || curr_val[0] == '|')
		{
			if (index == 0 || curr_val[1] == ';')
				return (make_errors(&argv[index], 2));
			next_val = argv[index + 1];
			if (next_val && (next_val[0] == ';' || next_val[0] == '&'
					|| next_val[0] == '|'))
				return (make_errors(&argv[index + 1], 2));
		}
	}
	return (0);
}

/**
 * perform_args - Function to handles the command arguments.
 * @exec_ret: variable for executing return value.
 *
 * Return: integer type.
 */
int perform_args(int *exec_ret)
{
	int exit_code = 0, index;
	char **argv, *input = NULL, **node;

	/* Read a line of input */
	input = read_args(input, exec_ret);
	if (!input)
		return (E_O_F);

	argv = my_strtok(input, " ");
	free(input);
	if (!argv)
		return (exit_code);

	/* Check the validity of arguments */
	if (verify_args(argv) != 0)
	{
		*exec_ret = 2;
		free_args(argv, argv);
		return (*exec_ret);
	}
	node = argv;

	/* If a semicolon is found, execute the previous arguments */
	for (index = 0; argv[index]; index++)
	{
		if (strn_cmp(argv[index], ";", 1) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			exit_code = call_args(argv, node, exec_ret);/* Call the command argv */
			argv = &argv[++index];/* Update the arguments and reset the index */
			index = 0;
		}
	}

	/* Find remaining arguments if they exist and execute them */
	if (argv)
		exit_code = call_args(argv, node, exec_ret);

	free(node);
	return (exit_code);
}

