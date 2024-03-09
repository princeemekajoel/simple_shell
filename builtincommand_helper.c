#include "shell.h"

/**
 * execute_exit - exit builtin
 * @tokens: tokenized commands
 */
void execute_exit(char **tokens)
{
	int size = 0;
	const char *error_msg;

	while (tokens[size] != NULL)
	{
		size++;
	}
	if (size > 2)
	{
		error_msg = "Error: too many arguments\n";
		write(STDERR_FILENO, error_msg, StringLength(error_msg));
	}
	else if (size == 2)
	{
		exit(atoi(tokens[1]));
	}
	else
	{
		exit(0);
	}
}

/**
 * execute_env - env builtin
 * @env: environment variable
 */
void execute_env(char **env)
{
	while (*env != NULL)
	{
		size_t len;

		len = StringLength(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * execute_cd - cd builtin
 * @tokens: tokenized commands
 * Return: 0 on success
 */
int execute_cd(char **tokens)
{
	char *folder_new = getcwd(NULL, 0);
	char *folder_prev = getenv("OLDPWD");

	if (tokens[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
		}
	}
	else if (my_strcmp(tokens[1], "-") == 0)
	{
		if (folder_prev == NULL)
			perror("cd: OLDPWD not set\n");
		else
		{
			if (chdir(folder_prev) != 0)
			{
				perror("cd");
			}
			write(STDERR_FILENO, folder_prev, StringLength(folder_prev));
			write(STDERR_FILENO, "\n", 1);
		}
	}
	else
	{
		if (chdir(tokens[1]) != 0)
		{
			perror("cd");
		}
	}
	if (folder_new == NULL)
	{
		perror("getcwd failed");
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", folder_new, 1);
	free(folder_new);
	return (1);
}

/**
 * shell_setenv - setenv builtin
 * @args: tokenized commands
 * Return: 0 or 1
 */
/* Implementation of the setenv command */
void shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "setenv: invalid arguments\n",
		StringLength("setenv: invalid arguments\n"));
	}
	else
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			write(STDERR_FILENO, "setenv: failed to set variable\n",
			StringLength("setenv: failed to set variable\n"));
		}
	}
}

/**
 * shell_unsetenv - cd builtin
 * @args: tokenized commands
 * Return: 0 or 1
 */
/*  Implementation of the unsetenv command */
void shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: invalid arguments\n",
		StringLength("unsetenv: invalid arguments\n"));
	}
	else
	{
		if (unsetenv(args[1]) != 0)
		{
			write(STDERR_FILENO, "unsetenv: failed to unset variable\n",
			StringLength("unsetenv: failed to unset variable\n"));
		}
	}
}

