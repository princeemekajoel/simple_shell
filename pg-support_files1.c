#include "shell.h"

/**
 * reading_input - reads input via getline
 * Return: Returns input from standard output
 */

char *reading_input()
{
	char *input = NULL;
	size_t input_size = 0;

	if (getline(&input, &input_size, stdin) == -1)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

/**
 * printStr - writes/print string to stdin
 * @str: string written
 * Return: Void
 */

void printStr(char *str)
{
	size_t len = StringLength(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * StringLength - count no. of characters in a string
 * @str: string whose length is calculated
 * Return: Length of string
 */

int StringLength(const char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

/**
 * writeStringToStderr - writes string to stderr
 * @str: Error message printed
 * Return: Void
 */

void writeStringToStderr(char *str)
{
	size_t len = StringLength(str);

	write(STDERR_FILENO, str, len);
}

/**
 * my_strcmp - compares two strings
 * @str1: the string 1
 * @str2: the second 2
 * Return: the diff btwn the ASCII values of the characters pointed by str
 */

int my_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
