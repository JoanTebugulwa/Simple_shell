#include "shell.h"

/**
 **_string_copy - A function that copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_string_copy(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 **_string_concatenate - A function that concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */


char *_string_concatenate(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (result);
}

/**
 * *_string_find_char - A function that locates
 * a character in a string
 *@string: the string to be parsed
 *@character: the character to look for
 *Return: (s) a pointer to the memory area s
 */


char *_string_find_char(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
