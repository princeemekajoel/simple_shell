#include "shell.h"

/**
 * custom_putenv - clone of putenv
 * @str: name value pair to be added to env
 * Return: 1 or 0
 */
int custom_putenv(char *str)
{
	int result = 0;
	char **new_environ = NULL;
	int i, j;

	if (!str || !*str || strchr(str, '=') == NULL)
	{
		return (-1);
	}

	new_environ = (char **)malloc(sizeof(char *) * (custom_environSize() + 2));
	if (!new_environ)
	{
		return (-1);
	}

	for (i = 0, j = 0; environ[i] != NULL; i++)
	{
		if (Strn_cmp(environ[i], str, custom_strchr(str, '=') - str) != 0)
		{
			new_environ[j++] = environ[i];
		}
		else
		{
			result = 1;
		}
	}
	new_environ[j++] = str;
	new_environ[j] = NULL;
	environ = new_environ;

	return (result);
}

/**
 * custom_strchr - custom strchr
 * @str: search string
 * @c: search char
 * Return: NULL or pointer to first occurence of c
 */
char *custom_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
		{
		return ((char *)str);
		}
		str++;
	}
	if (*str == c)
	{
		return ((char *)str);
	}
	return (NULL);
}

/**
 * custom_environSize - custom environSize
 * Return: size of current env variable
 */
int custom_environSize(void)
{
	int size = 0;
	char **envp = environ;

	while (*envp != NULL)
	{
		size++;
		envp++;
	}
	return (size);
}
