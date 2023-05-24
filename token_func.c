#include "aushell.h"

char **my_strtok(char *input, char *delimit);


/**
 * find_delim - Function to find the delimiter index.
 * @str: Variable for string searched.
 * @delimit: VAriable for delimiter value.
 *
 * Return: Integer type.
 */
int find_delim(char *str, char *delimit)
{
	int i = 0;
	int length = 0;

	while (*(str + i) && *(str + i) != *delimit)
	{
		length++;
		i++;
	}

	return (length);
}


/**
 * token_count - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delimit: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int token_count(char *str, char *delimit)
{
	int i;
	int tokens = 0;
	int length = 0;

	for (i = 0; *(str + i); i++)
		length++;

	for (i = 0; i < length; i++)
	{
		if (*(str + i) != *delimit)
		{
			tokens++;
			i += find_delim(str + i, delimit);
		}
	}

	return (tokens);
}


/**
 * my_strtok - Function to tokenizes a string.
 * @input: variable for string.
 * @delimit: variable to delimiter character to tokenize.
 *
 * Return: character type.
 */
char **my_strtok(char *input, char *delimit)
{
	char **tokens;
	int i = 0;
	int num_tokens, tok, word, ch;

	num_tokens = token_count(input, delimit);

	if (num_tokens == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (num_tokens + 2));

	if (!tokens)
		return (NULL);

	for (tok = 0; tok < num_tokens; tok++)
	{
		while (input[i] == *delimit)
			i++;

		word = find_delim(input + i, delimit);

		tokens[tok] = malloc(sizeof(char) * (word + 1));

		if (!tokens[tok])
		{
			for (i -= 1; i >= 0; i--)
				free(tokens[i]);

			free(tokens);
			return (NULL);
		}

		for (ch = 0; ch < word; ch++)
		{
			tokens[tok][ch] = input[i];
			i++;
		}

		tokens[tok][ch] = '\0';
	}

	tokens[tok] = NULL;
	tokens[tok + 1] = NULL;

	return (tokens);
}

