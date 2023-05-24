#include "aushell.h"

/**
 * error_msg_126 - Function to creates an error message
 *					when permission is denied.
 * @argv: variable for arguments array.
 *
 * Return: Error message character.
 */
char *error_msg_126(char **argv)
{
	char *error_msg;
	char *str;
	int length;

	/*Convert the history index to string*/
	str = my_itoa(history);

	/*Check if the converted string is successful*/
	if (!str)
		return (NULL);

	/*Calculate the length of error message*/
	length = str_len(command_name) + str_len(str) + str_len(argv[0]) + 24;

	/* Allocate memory for error message */
	error_msg = malloc(sizeof(char) * (length + 1));

	/*Check if memory allocation is successful*/
	if (!error_msg)
	{
		free(str);
		return (NULL);
	}

	/*Write the error message*/
	str_cpy(error_msg, command_name);
	str_cat(error_msg, ": ");
	str_cat(error_msg, str);
	str_cat(error_msg, ": ");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, ": Permission had been denied\n");

	/*Free indexed string */
	free(str);

	return (error_msg);
}

/**
 * error_msg_127 - Function to create an error message for command not found.
 * @argv: An array of arguments passed to the command.
 *
 * Return: Error message character.
 */
char *error_msg_127(char **argv)
{
	char *error_msg;
	char *str;
	int length;

	/*Convert the history index to string*/
	str = my_itoa(history);

	/*Check if the converted string is successful*/
	if (!str)
		return (NULL);

	/*Calculate the length of error message*/
	length = str_len(command_name) + str_len(str) + str_len(argv[0]) + 16;

	/*Allocate memory for error message*/
	error_msg = malloc(sizeof(char) * (length + 1));

	/*Check if memory allocation is successful*/
	if (!error_msg)
	{
		free(str);
		return (NULL);
	}

	/*Write the error message*/
	str_cpy(error_msg, command_name);
	str_cat(error_msg, ": ");
	str_cat(error_msg, str);
	str_cat(error_msg, ": ");
	str_cat(error_msg, argv[0]);
	str_cat(error_msg, ": command not found\n");

	/*Free indexed string*/
	free(str);

	return (error_msg);
}

