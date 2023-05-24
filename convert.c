#include "aushell.h"

/**
 * my_itoa - Function to converts integer to string.
 * @size: Variable for integer.
 *
 * Return: the number of string changed.
 */
char *my_itoa(int size)
{
	char *buf;
	int length = num_length(size);
	unsigned int index;

	/*Allocate memory for the buffer */
	buf = malloc(sizeof(char) * (length + 1));
	if (!buf)
		return (NULL);

	/*Set the null character to the end of buffer */
	buf[length] = '\0';

	if (size < 0)
	{
		index = size * -1;
		buf[0] = '-';
	}
	else
	{
		index = size;
	}

	/* Perform conversion here */
	length--;
	do {
		buf[length] = (index % 10) + '0';
		index /= 10;
		length--;
	} while (index > 0);

	/*Return the converted string*/
	return (buf);
}

/**
 * make_errors - Function to create errors.
 * @argv: variable for arguments array.
 * @error_no: Variable for error value.
 *
 * Return: integer type.
 */
int make_errors(char **argv, int error_no)
{
	char *error_msg;

	/*Choose the appropriate error message based on the error value*/
	if (error_no == -1)
		error_msg = env_error(argv);
	else if (error_no == 1)
		error_msg = alias_error(argv);
	else if (error_no == 126)
		error_msg = error_msg_126(argv);
	else if (error_no == 127)
		error_msg = error_msg_127(argv);
	else
	{
		/*Check if the first argument is "exit" or a shell operator*/
		if (str_cmp(argv[0], "exit") == 0 || argv[0][0] == ';'
		    || argv[0][0] == '&' || argv[0][0] == '|')
			error_msg = syntax_error(argv);
		else
			error_msg = cd_error(argv);
	}
	write(STDERR_FILENO, error_msg, str_len(error_msg));

	if (error_msg)
		free(error_msg);
	return (error_no);

}
/**
 * num_length - Function to calculate the number of digits.
 * @size: variable for integer
 *
 * Return: number of ingeter size.
 */
int num_length(int size)
{
	unsigned int index;
	int length = 1;

	/*Check if the integer is neagative*/
	if (size < 0)
	{
		length++;
		index = -size;
	}
	else
	{
		index = size;
	}

	/* Calculate the number of digits in the integer */
	while (size > 9)
	{
		length++;
		index /= 10;
	}

	return (length);
}


