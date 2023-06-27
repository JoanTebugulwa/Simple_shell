#include "shell.h"

/**
 * get_history_file_path - A function that gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */


char *get_history_file_path(info_t *info)
{
	char *home_dir = _getenv(info, "HOME=");
	
	if (!home_dir)
		return (NULL);

	char *history_file_path = malloc(sizeof(char) 
	* (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	
	if (!history_file_path)
		return (NULL);

	history_file_path[0] = '\0';
	_strcpy(history_file_path, home_dir);
	_strcat(history_file_path, "/");
	_strcat(history_file_path, HIST_FILE);

	return (history_file_path);
}


/**
 * write_history_to_file - A function that creates a file,
 * or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int write_history_to_file(info_t *info)
{
	ssize_t fd;
	char *file_path = get_history_file_path(info);
	list_t *node = NULL;

	if (!file_path)
		return (-1);

	fd = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_path);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_puts_to_file(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history_from_file - A function that reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history_from_file(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_path = get_history_file_path(info);

	if (!file_path)
		return (0);

	fd = open(file_path, O_RDONLY);
	free(file_path);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		file_size = st.st_size;

	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);

	read_length = read(fd, buffer, file_size);
	buffer[file_size] = '\0';

	if (read_length <= 0)
		return (free(buffer), 0);

	close(fd);

	for (i = 0; i < file_size; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			build_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buffer + last, line_count++);

	free(buffer);

	info->hist_count = line_count;

	while (info->hist_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);

	return (info->hist_count);
}

/**
 * build_history_list - A function that adds entry
 * to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - A function that renumbers the history linked
 * list after changes
 * @info: Structure containing potential arguments.
 * Used to maintain
 *
 * Return: the new history count
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int count = 0;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}

	return (info->hist_count = count);
}

