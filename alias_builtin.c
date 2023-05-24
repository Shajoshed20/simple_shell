#include "aushell.h"

char **replace_alias(char **argv);
int my_alias(char **argv, char **node);


/**
 * display_alias - function to prints the alias.
 * @alias: Pointer to an alias.
 */
void display_alias(Alias *alias)
{
	char *alias_name;
	int length = str_len(alias->name) + str_len(alias->value) + 4;

	alias_name = malloc(sizeof(char) * (length + 1));
	if (!alias_name)
		return;
	str_cpy(alias_name, alias->name);
	str_cat(alias_name, "='");
	str_cat(alias_name, alias->value);
	str_cat(alias_name, "'\n");

	write(STDOUT_FILENO, alias_name, length);
	free(alias_name);
}
/**
 * replace_alias - Function to replace matching alias.
 * @argv: variable for double pointer to arguments.
 *
 * Return: argument character.
 */
char **replace_alias(char **argv)
{
	Alias *current_alias;
	int index = 0;
	char *new_alias;

	if (str_cmp(argv[0], "alias") == 0)
		return (argv);

	/*Iterate through each argument*/
	while (argv[index])
	{
		current_alias = myalias;

		/*Search for alias that matched the user input*/
		while (current_alias)
		{
			if (str_cmp(argv[index], current_alias->name) == 0)
			{
				/*Allocate Memory for the new value */
				new_alias = malloc(sizeof(char) * (str_len(current_alias->value) + 1));
				if (!new_alias)
				{
					free_args(argv, argv);
					return (NULL);
				}

				/* Copy the alias value to the new value */
				str_cpy(new_alias, current_alias->value);

				/*Replace the input with the new value*/
				free(argv[index]);
				argv[index] = new_alias;

				/*index i is decreased to ensure the argument is reprocessed */
				index--;
				break;
			}
			current_alias = current_alias->next;
		}

		index++;
	}

	return (argv);
}

/**
 * rename_alias - Function to set the name of an alias that is exiting .
 * @variable_name: variable for alias name.
 * @value: variable for alias value.
 */
void rename_alias(char *variable_name, char *value)
{
	Alias *current_alias = myalias;
	int length, num, index;
	char *new_alias;

	/* Ignore the first character (', ") of the value */
	*value = '\0';
	value++;

	/* Calculate the length of the new value after removing quotes */
	length = str_len(value) - str_spn(value, "'\"");
	new_alias = malloc(sizeof(char) * (length + 1));
	if (!new_alias)
		return;

	/* Copy characters from value to new_value, excluding quotes */
	for (num = 0, index = 0; value[num]; num++)
	{
		if (value[num] != '\'' && value[num] != '"')
			new_alias[index++] = value[num];
	}
	new_alias[index] = '\0';

	/* Search for the alias with the given variable name */
	while (current_alias)
	{
		if (str_cmp(variable_name, current_alias->name) == 0)
		{
			/* Free the previous value and set the new value */
			free(current_alias->value);
			current_alias->value = new_alias;
			break;
		}
		current_alias = current_alias->next;
	}

	/* If the alias is not found, add a new alias */
	if (!current_alias)
		add_alias_node(&myalias, variable_name, new_alias);
}

/**
 * my_alias - Function for alias builtin command.
 * @argv: variable for arguments array.
 * @node: variable for double pointer.
 *
 * Return: integer type.
 */
int my_alias(char **argv, char **node)
{
	int exit_code = 0;
	int index = 0;
	char *value;
	Alias *current_alias = myalias;

	(void) **node;

	/* Print all aliases if no arguments provided */
	if (argv[0] == NULL)
	{
		while (current_alias != NULL)
		{
			display_alias(current_alias);
			current_alias = current_alias->next;
		}
		return (exit_code);
	}

	/* Process each argument */
	while (argv[index] != NULL)
	{

		value = str_chr(argv[index], '=');

		/* If argument does not contain '=', search for alias */
		if (value == NULL)
		{
			while (current_alias != NULL)
			{
				if (str_cmp(argv[index], current_alias->name) == 0)
				{
					display_alias(current_alias);
					break;
				}
				current_alias = current_alias->next;
			}

			/* If alias not found, create error */
			if (current_alias == NULL)
				exit_code = make_errors(argv + index, 1);
		}
		else
		{
			rename_alias(argv[index], value);
		}

		index++;
	}

	return (exit_code);
}

