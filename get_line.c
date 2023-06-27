#include "shell.h"

/**
 * buffer_input - buffers chained commands
 *
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t bytesRead = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		bytesRead = getline(buf, &len_p, stdin);
#else
		bytesRead = custom_getline(info, buf, &len_p);
#endif
		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->lineCountFlag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->historyCount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = bytesRead;
				info->commandBuffer = buf;
			}
		}
	}
	return (bytesRead);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t bytesRead = 0;
	char **buf_p = &(info->arguments), *p;

	_putchar(BUF_FLUSH);
	bytesRead = buffer_input(info, &buf, &len);
	if (bytesRead == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->commandBufferType = CMD_NORM;
		}

		*buf_p = p;
		return (strlen(p));
	}

	*buf_p = buf;
	return (bytesRead);
}

/**
 * read_buffer - reads a buffer
 *
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: bytesRead
 */

ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);
	bytesRead = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;
	return (bytesRead);
}

/**
 * custom_getline - gets the next line of input from STDIN
 *
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */

int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (i == len)
		i = len = 0;

	bytesRead = read_buffer(info, buf, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reallocate_memory(p, size, size ? size + k : k + 1);
	if (!new_p)
		return (p ? (free(p), -1) : -1);

	if (size)
		strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * interruptHandler - blocks ctrl-C
 *
 * @sigNum: the signal number
 *
 * Return: void
 */

void interruptHandler(__attribute__((unused))int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
