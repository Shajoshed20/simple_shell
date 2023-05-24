#include "aushell.h"

int shell_run(char **command_args, char **orginal_args);
/**
 * main - Entry point of the program.
 * @argc: Variable for the number of parameters passed.
 * @argv: Variable for the name of the program.
 * Return: Always 0 (Success).
 */

int main(int argc, char *argv[])
{
	int ret_value = 0, cmd_return;
	int *exec_return = &cmd_return;
	char *shell_prompt = HOME, *new_line = "\n";

	command_name = argv[0];
	history = 1;
	myalias = NULL;
	signal(SIGINT, sig_handler);

	*exec_return = 0;
	environ = copy_environ();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret_value = file_pro_cmd(argv[1], exec_return);
		free_env();
		free_alias_node(myalias);
		return (*exec_return);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret_value != E_O_F && ret_value != EXIT)
			ret_value = perform_args(exec_return);

		free_env();
		free_alias_node(myalias);
		return (*exec_return);
	}

	while (1)
	{
		write(STDOUT_FILENO, shell_prompt, str_len(shell_prompt));
		ret_value = perform_args(exec_return);
		if (ret_value == E_O_F || ret_value == EXIT)
		{
			if (ret_value == E_O_F)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_node(myalias);
			exit(*exec_return);
		}
	}

	free_env();
	free_alias_node(myalias);
	return (*exec_return);
}


/**
 * sig_handler - Prints a new prompt when receiving a signal.
 * @signal_num: The signal number.
 */
void sig_handler(int signal_num)
{
	(void) signal_num; /* Unused parameter */

	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, HOME, 3);
}

/**
 * shell_run - Function to execute a command in a child process.
 * @command_args: An array of strings containing the command
 *											and its arguments.
 * @orginal_args: A double pointer containing the original input line.
 *
 * Return: On success - The exit value of the last executed command.
 *				On failure: an error code.
 */
int shell_run(char **command_args, char **orginal_args)
{
	pid_t child_pid;
	int status, file_status = 0, exit_code = 0;
	char *command_name = command_args[0];

	if (command_name[0] != '/' && command_name[0] != '.')
	{
		file_status = 1;
		command_name = find_executable_path(command_name);
	}

	if (!command_name || (access(command_name, F_OK) == -1))
	{
		if (errno == EACCES)
			exit_code = make_errors(command_args, 126);
		else
			exit_code = make_errors(command_args, 127);
	}
	else
	{
		child_pid = fork(); /* Create a child process */
		if (child_pid == -1)
		{
			if (file_status)
				free(command_name);
			perror("Process error: ");
			return (1);
		}

		if (child_pid == 0)/* Child process */
		{
			execve(command_name, command_args, environ);
			if (errno == EACCES)
				exit_code = make_errors(command_args, 126);
			/* Free allocated memory */
			free_env();
			free_args(command_args, orginal_args);
			free_alias_node(myalias);
			_exit(exit_code);
		}
		else
		{
			wait(&status);
			exit_code = WEXITSTATUS(status);
		}
	}

	if (file_status)
		free(command_name);

	return (exit_code);
}

