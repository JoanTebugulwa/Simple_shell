#include "shell.h"

/**
 * clearInfo - initializes info_t struct
 * @info: struct address
 *
 * Return: returns nothing
 */

void clearInfo(info_t *info)
{
	info->argument = NULL;
	info->argumentVector = NULL;
	info->path = NULL;
	info->argumentCount = 0;
}

/**
 * setInfo - initializes info_t struct
 *
 * @info: struct address
 * @av: argument vector
 *
 * Return: returns nothing
 */

void setInfo(info_t *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->argument)
	{
		info->argumentVector = strtow(info->argument, " \t");
		if (!info->argumentVector)
		{
			info->argumentVector = malloc(sizeof(char *) * 2);
			if (info->argumentVector)
			{
				info->argumentVector[0] = _strdup(info->argument);
				info->argumentVector[1] = NULL;
			}
		}
		for (i = 0; info->argumentVector && info->argumentVector[i]; i++)
			;
		info->argumentCount = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 *
 * @info: struct address
 * @all: true if freeing all fields
 *
 * Return: void
 */

void freeInfo(info_t *info, int all)
{
	ffree(info->argumentVector);
	info->argumentVector = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->commandBuffer)
			free(info->argument);
		if (info->environment)
			freeList(&(info->environment));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		ffree(info->environmentVariables);
		info->environmentVariables = NULL;
		bfree((void **)info->commandBuffer);
		if (info->readFileDescriptor > 2)
			close(info->readFileDescriptor);
		_putchar(BUF_FLUSH);
	}
}
