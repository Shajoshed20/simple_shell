#include "aushell.h"


/**
 * env_help - Function to print help information for the 'env' command.
 */
void env_help(void)
{
	char *help_msg = "env: env\n\tPrints the environment.\n";

	write(STDOUT_FILENO, help_msg, str_len(help_msg));
}


/**
 * setenv_help - Function to print help information builtin command 'setenv'.
 */
void setenv_help(void)
{
	char *senv_msg = "setenv: setenv \n";

	write(STDOUT_FILENO, senv_msg, str_len(senv_msg));

	senv_msg = "\tSet values of environment variables, ";
	write(STDOUT_FILENO, senv_msg, str_len(senv_msg));

	senv_msg = "or modifies an existing one.\n";
	write(STDOUT_FILENO, senv_msg, str_len(senv_msg));

	senv_msg = "\n\tOtherwise on fail, prints a message to Stderr.\n";
	write(STDOUT_FILENO, senv_msg, str_len(senv_msg));
}

/**
 * unsetenv_help - Function to print help information for builtin command
 * 'unsetenv'.
 */
void unsetenv_help(void)
{
	char *usenv_msg = "unsetenv: unsetenv [NAME]\n";

	write(STDOUT_FILENO, usenv_msg, str_len(usenv_msg));
	usenv_msg = "\tRemove each NAME from the list of";
	write(STDOUT_FILENO, usenv_msg, str_len(usenv_msg));
	usenv_msg = " defined environment variables.\n";
	write(STDOUT_FILENO, usenv_msg, str_len(usenv_msg));
	usenv_msg = "\n\tOtherwise on fail, a NAME does not exist as alias.\n";
	write(STDOUT_FILENO, usenv_msg, str_len(usenv_msg));
}

