#include "aushell.h"

/**
 * str_cpy - Function to copy the string.
 * @dest: Variable for destination string.
 * @src: Variable for the source string.
 *
 * Return: Pointer to dest.
 */
char *str_cpy(char *dest, const char *src)
{
	size_t index;

	for (index = 0; src[index] != '\0'; index++)
		dest[index] = src[index];
	dest[index] = '\0';
	return (dest);
}

/**
 * str_cat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *str_cat(char *dest, const char *src)
{
	char *exit_code = dest;
	const char *src_buf = src;

	/* check for exit code */
	while (*exit_code != '\0')
		exit_code++;

	/* check the while condition*/
	while (*src_buf != '\0')
		*exit_code++ = *src_buf++;
	*exit_code = '\0';
	return (dest);
}

/**
 * strn_cat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @num: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *strn_cat(char *dest, const char *src, size_t num)
{
	size_t index;
	size_t s = str_len(dest);

	/* check for condtion*/
	for (index = 0; index < num && src[index] != '\0'; index++)
		dest[s + index] = src[index];

	dest[s + index] = '\0';

	return (dest);
}


/**
 * str_len - Function to returns the length of a string.
 * @str: variable the string whose length to check.
 *
 * Return: The integer length of the string.
 */
int str_len(const char *str)
{
	int index = 0;

	/* check length*/
	if (!str)
		return (0);
	for (index = 0; str[index]; index++)
		;
	return (index);
}

