#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * list_to_strings - Returns an array of strings from a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t count = list_len(head);
	char **strs;
	char *str;
	size_t i;

	if (head == NULL || count == 0)
		return (NULL);

	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);

	for (i = 0; node != NULL; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			for (size_t j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * node_starts_with - Returns the node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node != NULL)
	{
		p = starts_with(node->str, prefix);
		if (p != NULL && (c == -1 || *p == c))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head != NULL)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}

