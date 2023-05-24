#include "aushell.h"

void check_line(char **input, ssize_t line_len);
ssize_t cal_new_size(char *input);

/**
 * cal_new_size - Function to calculate new length of line
 * @input: variable for line input
 *
 * Return: The size of line input.
 */
ssize_t cal_new_size(char *input)
{
	size_t i = 0;
	ssize_t new_size = 0;
	char current;
	char next;

	while (input[i])
	{
		current = input[i];
		next = input[i + 1];
		if (current == '#')
		{
			/* If '#' is at the beginning or after a space*/
			if (i == 0 || input[i - 1] == ' ')
			{
				input[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				/* Handle multiple semicolons and spaces */
				if (next == ';' && input[i - 1] != ' ' && input[i - 1] != ';')
				{
					new_size += 2;
					i++;
					continue;
				}
				else if (input[i - 1] == ';' && next != ' ')
				{
					new_size += 2;
					i++;
					continue;
				}
				/*Increases the new_size for non-space characters*/
				if (input[i - 1] != ' ')
					new_size++;
				if (next != ' ')
					new_size++;
			}
			else
				get_operator(&input[i], &new_size);/*Check for logic operators*/
		}
		else if (current == ';')
		{
			/* Handle semicolons at the beginning of the input*/
			if (i != 0 && input[i - 1] != ' ')
				new_size++;
			if (next != ' ' && next != ';')
				new_size++;
		}

		new_size++;
		i++;
	}
	return (new_size);
}

/**
 * check_line - Function to read line from standard input.
 * @input: A pointer to a line line_len from standard input.
 * @line_len: Variable for line length.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void check_line(char **input, ssize_t line_len)
{
	char prev_char, curr_char, next_char;
	size_t i = 0, j = 0;
	char *old_line, *new_line;
	ssize_t new_size;

	new_size = cal_new_size(*input);
	if (new_size == line_len - 1)
		return;

	new_line = malloc(new_size + 1);
	if (!new_line)
		return;

	old_line = *input;
	while (old_line[i])
	{
		curr_char = old_line[i];
		next_char = old_line[i + 1];

		if (i != 0)
		{
			prev_char = old_line[i - 1];

			if (curr_char == ';')
			{
				if (next_char == ';' && prev_char != ' ' && prev_char != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					i++;
					continue;
				}
				else if (prev_char == ';' && next_char != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					i++;
					continue;
				}

				if (prev_char != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next_char != ' ')
					new_line[j++] = ' ';
				i++;
				continue;
			}
			else if (curr_char == '&')
			{
				if (next_char == '&' && prev_char != ' ')
					new_line[j++] = ' ';
				else if (prev_char == '&' && next_char != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					i++;
					continue;
				}
			}
			else if (curr_char == '|')
			{
				if (next_char == '|' && prev_char != ' ')
					new_line[j++]  = ' ';
				else if (prev_char == '|' && next_char != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					i++;
					continue;
				}
			}
		}
		else if (curr_char == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next_char != ' ' && next_char != ';')
				new_line[j++] = ' ';
			i++;
			continue;
		}

		new_line[j++] = old_line[i];
		i++;
	}

	new_line[j] = '\0';

	free(*input);
	*input = new_line;
}

/**
 * get_operator - function to get the operator in use.
 * @input: variable for input argument array.
 * @new_size: Pointer to new_size in get_new_size function.
 */
void get_operator(char *input, ssize_t *new_size)
{
	char prev_char;
	char curr_char;
	char next_char;

	prev_char = *(input - 1);
	curr_char = *input;
	next_char = *(input + 1);

	/* Check for && and || Logic Operators*/
	if (curr_char == '&')
	{
		if (next_char == '&' && prev_char != ' ')
			(*new_size)++;
		else if (prev_char == '&' && next_char != ' ')
			(*new_size)++;
	}
	else if (curr_char == '|')
	{
		if (next_char == '|' && prev_char != ' ')
			(*new_size)++;
		else if (prev_char == '|' && next_char != ' ')
			(*new_size)++;
	}
}
