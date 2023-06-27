#include "shell.h"

/**
 * err_atoi - converts a string to an integer
 *
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int err_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - prints an error message
 *
 * @info: the parameter and return info struct
 * @error_string: string containing specified error type
 *
 * Return: void
 */

void print_error_message(info_t *info, char *error_string)
{
	_eputs(info->file_name);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 *
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */

int print_decimal(int input, int fd)
{
	int (*_putchar_func)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		_putchar_func = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		_putchar_func('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			_putchar_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	_putchar_func('0' + current);
	count++;

	return (count);
}

/**
 * convert_number_to_string - converts a number to a string
 *
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string representation of the number
 */

char *convert_number_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments_from_string - replaces first instance of '#' with '\0'
 *
 * @str: address of the string to modify
 *
 * Return: void
 */

void remove_comments_from_string(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '#' && (!i || str[i - 1] == ''))
		{
			str[i] = '\0';
			break;
		}
}