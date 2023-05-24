#include "aushell.h"

/**
 * all_help - function to display all help for builtin commands.
 */
void all_help(void)
{
	char *help_msg = "AUshell\nThese include cutom made commands for shell.\n";

	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "Enter 'help' to see current list.\nType 'help name' to display ";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "more information on the function 'name'.\n\n  cd   \t";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "[DIRECTORY]\n  alias    \talias   ";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "alias [NAME[='VALUE']...]\n  exit   \texit [STATUS]\n  env    \t";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "env\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
}

/**
 * alias_help - Function to display help for builtin command 'alias'.
 */
void alias_help(void)
{
	char *alias_msg = "alias: alias [NAME[='VALUE']..]\n";

	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = "\tDefines or display aliases.\n";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = "\n\talias: prints the list of aliases in the reusable ";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = "form `alias NAME=VALUE' on standard output.\n\talias name ";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = " [name2 ...]: prints the aliases name, name2, etc. one";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = "per line, in the form NAME='VALUE'.\n\talias NAME='VALUE'";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = " [...]: Defines an alias for each NAME whose VALUE is given. ";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = "For NAME alias returns true unless a NAME is supplied \n";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
	alias_msg = "for whichno alias has been defined.";
	write(STDOUT_FILENO, alias_msg, str_len(alias_msg));
}

/**
 * cd_help - function to display help for builtin command'cd'.
 */
void cd_help(void)
{
	char *cd_msg = "cd: cd\n\tChange the shell working directory.";

	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
	cd_msg = "\n\n\tThe default DIRECTORY is the value of the shell.\n";
	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
	cd_msg = "\n\tIf no argument is provided, the command is";
	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
	cd_msg = " then interpreted as cd HOME. If the argument '-'";
	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
	cd_msg = " is given, the command is interpreted as cd $OLDPWD.\n";
	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
	cd_msg = "\n\tThe environment variables PWD and OLDPWD ";
	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
	cd_msg = "are then updated after a change of directory.\n";
	write(STDOUT_FILENO, cd_msg, str_len(cd_msg));
}

/**
 * exit_help - Function to diaplay help for builtin command 'exit'.
 */
void exit_help(void)
{
	char *exit_msg = "exit: exit [STATUS]\n\tTo exits the shell.\n\n ";

	write(STDOUT_FILENO, exit_msg, str_len(exit_msg));
	exit_msg = "\tThe STATUS argument is the integer used to ";
	write(STDOUT_FILENO, exit_msg, str_len(exit_msg));
	exit_msg = "exit the shell. If no argument is given, the command is ";
	write(STDOUT_FILENO, exit_msg, str_len(exit_msg));
	exit_msg = " interpreted as exit 0.\n";
	write(STDOUT_FILENO, exit_msg, str_len(exit_msg));
}

/**
 * helps_help - function to display help for builtin command 'help'.
 */
void helps_help(void)
{
	char *help_msg = "help: help\n\tSee all available AUshell";

	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = " builtin commands.\n\n      help [BUILTIN NAMES]";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "\n\tSee specific information on each ";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
	help_msg = "builtin command.\n";
	write(STDOUT_FILENO, help_msg, str_len(help_msg));
}

