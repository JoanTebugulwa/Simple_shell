#include "shell.h"

/**
 * bfree - A function that frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}

