#include "aushell.h"

/**
 * free_env - Function to free the environment copy.
 */

void free_env(void)
{
	int env_size = 0;

	while (environ[env_size])
	{
		free(environ[env_size]);
		env_size++;
	}

	free(environ);

}

/**
 * copy_environ - Function to create a copy of environment.
 *
 * Return: On success, a double pointer to the new copy,
 *							otherwise NULL.
 */
char **copy_environ(void)
{
	char **new_env;
	size_t env_size;
	int i;
	size_t env_len;

	for (env_size = 0; environ[env_size]; env_size++)
		;

	new_env = malloc(sizeof(char *) * (env_size + 1));

	/*when new environment is null*/
	if (new_env == NULL)
		return (NULL);

	/*for the condition of index in environ variable*/
	for (i = 0; environ[i]; i++)
	{
		env_len = str_len(environ[i]) + 1;
		new_env[i] = malloc(env_len);

		if (new_env[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}

		str_cpy(new_env[i], environ[i]);
	}

	new_env[i] = NULL;
	return (new_env);
}


/**
 * my_getenv- Function to gets the value of an environment variable.
 * @name: Variable for name of the environment variable.
 *
 * Return: If the environment variable exists - a pointer to its value.
 *         Otherwise - NULL.
 */
char **my_getenv(const char *name)
{
	int len = str_len(name);
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strn_cmp(name, environ[i], len) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
