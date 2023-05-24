#include "aushell.h"

/**
 * add_node_end - Function to adds a node to the end of a list.
 * @head: Variable for address pointer to the head node.
 * @dir_path: The directory path for the new node.
 *
 * Return: A pointer to size of list.
 */
list_t *add_node_end(list_t **head, char *dir_path)
{
	list_t *new_node, *last_node;

	if (!head)
		return (NULL);

	last_node = *head;
	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = dir_path;
	new_node->next = NULL;

	if (*head)
	{
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}


/**
 * free_node - Function to free a list_t list.
 * @head: Variable address of pointer to head node.
 */
void free_node(list_t *head)
{
	list_t *current_node, *next_node;

	current_node = head;
	if (!current_node)
		return;
	while (current_node)
	{
		next_node = current_node->next;

		free(current_node->dir);
		free(current_node);

		current_node = next_node;
	}
}


/**
 * add_alias_node - Function to adds a node to the end of alias list.
 * @head: Variable for  address of pointer to the head node.
 * @name: VAriable for name of the new alias.
 * @value: The value of the new alias to be added.
 *
 * Return: size of the new node.
 */

Alias *add_alias_node(Alias **head, char *name, char *value)
{
	Alias *new_alias, *last_node;

	if (!head)
		return (NULL);

	new_alias = malloc(sizeof(Alias));
	if (!new_alias)
		return (NULL);

	new_alias->next = NULL;
	new_alias->name = malloc(sizeof(char) * (str_len(name) + 1));
	/*when no new alias name*/
	if (!new_alias->name)
	{
		free(new_alias);
		return (NULL);
	}

	new_alias->value = value;
	str_cpy(new_alias->name, name);
	/*If head is not empty*/
	if (*head)
	{
		last_node = *head;
		while (last_node->next)
			last_node = last_node->next;

		last_node->next = new_alias;
	}
	else
		*head = new_alias;

	return (new_alias);
}

/**
 * free_alias_node - Function to free an alias_t list.
 * @alias_head: Variable for head of list.
 */
void free_alias_node(Alias *alias_head)
{
	Alias *current_alias, *alias_next;

	current_alias = alias_head;

	if (!current_alias)
		return;

	/*When current alias is valid*/
	while (current_alias)
	{
		alias_next = current_alias->next;

		free(current_alias->name);
		free(current_alias->value);
		free(current_alias);

		current_alias = alias_next;
	}
}

