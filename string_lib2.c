#include "aushell.h"

/**
 * str_chr - Function locate a character in a string.
 * @str: Vairable for the string to be parsed.
 * @ch: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *str_chr(char *str, char ch)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ch)
			return (str + i);
	}

	return (NULL);
}

/**
 * str_spn - Function to gets the length of a prefix substring.
 * @str: variable for string.
 * @prefix: Variable for prefix.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int str_spn(char *str, char *prefix)
{
	int i, size = 0;

	while (*str)
	{
		for (i = 0; prefix[i]; i++)
		{
			if (*str == prefix[i])
			{
				size++;
				break;
			}
		}
		str++;
	}
	return (size);
}

/**
 * str_cmp - this function compare two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: return a number depends os the result for comparation.
*/
int str_cmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
	}
	return (0);
}

/**
 * strn_cmp - Compare two strings.
 * @str1: Pointer to a string.
 * @str2: Pointer to a string.
 * @num: The limit bytes of comparison.
 *
 * Return: Integer type.
 */
int strn_cmp(const char *str1, const char *str2, size_t num)
{
	size_t i;
	int diff;

	if (str1 == NULL || str2 == NULL)
		return (-1);

	for (i = 0; str1[i] && str2[i] && i < num; i++)
	{
		diff = str1[i] - str2[i];
		if (str1[i] > str2[i])
			return (diff);
		else if (str1[i] < str2[i])
			return (diff);
	}
	return (0);
}

