#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: adress of struct
 *
 * Return: 1 if interactive, 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is delimeter
 * @c: char to be checked
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
		}
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: Input character
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - A function that converts a string to an integer
 * @s: the string to convert
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int sign = 1;
	unsigned int result = 0;
	int flag = 0;

	while (*s && flag != 2)
	{
		if (*s == '-')
			sign *= -1;

		if (*s >= '0' && *s <= '9')
		{
			flag = 1;
			result *= 10;
			result += (*s - '0');
		}
		else if (flag == 1)
			flag = 2;

		s++;
	}

	return (sign * (int)result);
}
