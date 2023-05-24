#include "aushell.h"

/**
 * env_error - Function to display error message for environment.
 * @argv: variable for argument array.
 *
 * Return: error message character.
 */
char *env_error(char **argv)
{
	char *error_msg, *str;
	int length;

	/*Convert the current history index to a string */
	str = my_itoa(history);
	if (!str)
		return (NULL);

	/*Decrement the argv pointer to get command name */
		argv--;

	/* Calculate the length of the error message */
	length = str_len(command_name) + str_len(str) + str_len(argv[0]) + 45;

	/* Allocate memory for the error message */
	error_msg = malloc(sizeof(char) * (length + 1));
	if (!error_msg)
	{
		free(str);
		return (NULL);
	}

	/*Write the Error Message Constructors*/
	str_cpy(error_msg, command_name);
	str_cat(error_msg, ": ");
	str_cat(error_msg, str);
	str_cat(error_msg, ": ");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, ": Unable to make changes to Environment\n");

	/*Free memory used for str index*/
	free(str);

	return (error_msg);
}

/**
 * alias_error - Function to creates an error message for my_alias.
 * @argv: variable for argument array.
 *
 * Return: Error mesage character.
 */
char *alias_error(char **argv)
{
	char *error_msg;
	int length;

	/*Calculate the length og error message*/
	length = str_len(command_name) + str_len(argv[0]) + 13;

	/* Allocate memory for the error message*/
	error_msg = malloc(sizeof(char) * (length + 1));
	if (!error_msg)
		return (NULL);

	str_cpy(error_msg, "This alias: ");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, " cannot be found\n");

	return (error_msg);
}

/**
 * exit_error - Function for creating an error message for my_exit errors.
 * @argv: variable for arguments array.
 *
 * Return: Error mesage character.
 */
char *exit_error(char **argv)
{
	char *error_msg;
	char *str;
	int length;

	/*convert the current history index to a string*/
	str = my_itoa(history);
	if (!str)
		return (NULL);

	/*Calculate the length of the error message*/
	length = str_len(command_name) + str_len(str) + str_len(argv[0]) + 27;

	/*allocate memory for the error message*/
	error_msg = malloc(sizeof(char) * (length + 1));
	if (!error_msg)
	{
		free(str);
		return (NULL);
	}

	str_cpy(error_msg, command_name);
	str_cat(error_msg, ": ");
	str_cat(error_msg, str);
	str_cat(error_msg, ": exit: Wrong number status: ");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, "\n");

	free(str);
	return (error_msg);
}

/**
 * cd_error - Function to create an error message for my_cd errors.
 * @argv: variable for arguments array.
 *
 * Return: Error mesage character.
 */
char *cd_error(char **argv)
{
	char *error_msg;
	char *str;
	int length;

	/*Conver the current history index to string*/
	str = my_itoa(history);
	if (!str)
		return (NULL);

	/*Check if the first argument is a flag*/
	if (argv[0][0] == '-')
		argv[0][2] = '\0';

	/*Calcuate the length of the error message*/
	length = str_len(command_name) + str_len(str) + str_len(argv[0]) + 24;

	/*Allocate Memory for error messgae*/
	error_msg = malloc(sizeof(char) * (length + 1));
	if (!error_msg)
	{
		free(str);
		return (NULL);
	}

	/* Write the error message */
	str_cpy(error_msg, command_name);
	str_cat(error_msg, "; ");
	str_cat(error_msg, str);
	if (argv[0][0] == '-')
		str_cat(error_msg, ": cd: File or Directory doesn't exit ");
	else
		str_cat(error_msg, ": cd: can't perform change directory function ");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, "\n");

	/*Free memory used for string indexing*/
	free(str);

	return (error_msg);
}

/**
 * syntax_error - Creates an error message for syntax errors.
 * @argv: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *syntax_error(char **argv)
{
	char *error_msg;
	char *str;
	int length;

	/*Convert the history index to string*/
	str = my_itoa(history);
	if (!str)
		return (NULL);

	/*Calculate the length of the error message*/
	length = str_len(command_name) + str_len(str) + str_len(argv[0]) + 33;

	/*Allocate memory for error messgae*/
	error_msg = malloc(sizeof(char) * (length + 1));
	if (!error_msg)
	{
		free(str);
		return (NULL);
	}

	/*Write the error message*/
	str_cpy(error_msg, command_name);
	str_cat(error_msg, ": ");
	str_cat(error_msg, str);
	str_cat(error_msg, ": Error in syntax: \"");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, "\" not input expected\n");

	/*Free memory used for string indexing*/
	free(str);

	return (error_msg);
}

