#include "shell.h"

/**
 * concat_str - joins two strings together
 * @str1: string concetenated
 * @str2: string joined to str1
 * Return: str1 and str2 combined
 */

char *concat_str(char *str1, char *str2)
{
	int len1 = StringLength(str1);
	int len2 = StringLength(str2);
	char *result = malloc(len1 + len2 + 1);

	if (result == NULL)
	{
		perror("Failed to allocate memory for concatenated string");
		exit(1);
	}
	result = Str_cpy(result, str1);
	result = Str_cat(result, str2);
	return (result);
}

/**
 * Str_cpy - copies contents of one string to another string
 * @dest: copying destination
 * @src: string copied
 * Return: string copied
 */

char *Str_cpy(char *dest, const char *src)
{
	char *originalDest = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (originalDest);
}

/**
 * Str_cat - concatenates two strings
 * @dest: destiation
 * @src: string constant
 * Return: joined string
 */

char *Str_cat(char *dest, const char *src)
{
	char *originalDest = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (originalDest);
}

/**
 * Strn_cmp - compares two strings, checks if they are equal
 * @s1: string one compared
 * @s2: string compared with string one
 * @n: compares the first n characters of s1 and s2.
 * Return: 0 on sucess
 */
int Strn_cmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (*s1 == '\0' || *s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

/**
 * strd_up - copies the contents of the input string str to the new memory
 * @str: string copied
 * Return: a pointer to the new string.
 */

char *strd_up(const char *str)
{
	size_t len = StringLength(str) + 1;
	char *new_str = malloc(len);

	if (new_str == NULL)
		return (NULL);
	memcpy(new_str, str, len);
	return (new_str);
}
