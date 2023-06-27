#include "shell.h"

#include "shell.h"

/**
 * _eputs - A function that prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - A function that writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

/**
 * _putfd - A funtion that writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

/**
 * _putsfd - A function that prints an input string
 * @str: the string to be printed
 * @fd: the file-descriptor to write to
 *
 * Return: the number of chars put
 */

int _putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += _putfd(*str++, fd);
	}

	return (count);
}

