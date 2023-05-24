#include "aushell.h"

int my_setenv(char **argv, char **node);

/**
 * my_env - Function to print the current environment.
 * @argv: variable for argument array.
 * @node: variable for arguments first node.
 *
 * Return: Always Success (0)
 */
int my_env(char **argv, char **node)
{
	int index = 0;
	char new_line = '\n';
	size_t env_len;

	(void) **node;

	if (!environ)
		return (-1);

	/* Print environment variables until NULL is encountered */
	while (environ[index])
	{
		env_len = str_len(environ[index]);

		write(STDOUT_FILENO, environ[index], env_len);
		write(STDOUT_FILENO, &new_line, 1);

		index++;
	}

	(void)argv;
	return (0);
}

/**
 * my_setenv - Function to set environment variable.
 * @argv: variable for argument array.
 * @node: variable for argument first node.
 *
 * Return: Always 0 (Success)
 */
int my_setenv(char **argv, char **node)
{
	size_t size = 0;
	int i = 0;
	char **env_var = NULL, **new_environ, *new_value;

	(void) **node;

	if (!argv[0] || !argv[1])
		return (make_errors(argv, -1));

	new_value = malloc(str_len(argv[0]) + 1 + str_len(argv[1]) + 1);
	if (!new_value)
		return (make_errors(argv, -1));

	str_cpy(new_value, argv[0]);
	str_cat(new_value, "=");
	str_cat(new_value, argv[1]);

	env_var = my_getenv(argv[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}

	/* Get the size of the environ array */
	while (environ[size])
		size++;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (make_errors(argv, -1));
	}

	/*Copy the values of environ to the new_environ */
	while (environ[i])
	{
		new_environ[i] = environ[i];
		i++;
	}

	free(environ);
	environ = new_environ;
	environ[i] = new_value;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * my_unsetenv - Function to delete an environmental variable.
 * @argv: variable for argument array.
 * @node: variable for argument first node.
 *
 * Return: Always 0 (Success)
 */
int my_unsetenv(char **argv, char **node)
{
	char **env_var, **new_environ;
	size_t size = 0;
	int i = 0;
	int i2 = 0;

	(void) **node;

	if (!argv[0])
		return (make_errors(argv, -1));
	env_var = my_getenv(argv[0]);
	if (!env_var)
		return (0);

	while (environ[size])
		size++;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (make_errors(argv, -1));

	while (environ[i])
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			i++;
			continue;
		}
		new_environ[i2] = environ[i];
		i++;
		i2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

