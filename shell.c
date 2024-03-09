#include "shell.h"

/**
 * main - Entry point og the program
 * @argc: argc
 * @argv: argv
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	char *input = NULL;
	char *tokens[MAX_NUM_TOKENS];
	int num_tokens;

	if (argc > 1 && my_strcmp(argv[0], "./hsh") == 0)
	{
		file_input(argc, argv);
		exit(0);
	}
	while (1)
	{
		if (isatty(0))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		}
		input = reading_input();
		if (input == NULL)
		{
			if (isatty(0))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			free(input);
			exit(0);
		}
		if (strchr(input, ';') != NULL)
			handle_semicolon(input);
		else
		{
			num_tokens = tokenize(input, tokens, MAX_NUM_TOKENS);
			if (num_tokens > 0 && strcmp(tokens[0], "alias") != 0)
				execute(tokens);
		}
		free(input);
	}
	return (0);
}

/**
 * tokenize - breaks a string into tokens using strtok() function
 * @input: input to be tokenized.
 * @tokens: array holding resulting tokens
 * @max_tokens: max tokens extracted from input string
 * Return: n-tokens
 */

int tokenize(char *input, char **tokens, int max_tokens)
{
	int num_tokens = 0;
	char *token = strtok(input, " \n");

	while (token != NULL && num_tokens < max_tokens)
	{
		if (token[0] == '#')
		{
			break;
		}
		tokens[num_tokens] = token;
		num_tokens++;
		token = strtok(NULL, " \n");
	}
	tokens[num_tokens] = NULL;
	return (num_tokens);
}

/**
 * command_checker - checks if the command is a built in or located in PATH
 * @tokens: command pointer
 * Return: command path
 */

char *command_checker(char **tokens)
{
	char *path;
	LL *pathLL;
	char *builtins[6] = {"exit", "env", "cd", "unsetenv", "setenv", NULL};
	int i;

	for (i = 0; builtins[i]; i++)
	{
		if (my_strcmp(tokens[0], builtins[i]) == 0)
		{
			execute_builtins(tokens, environ);
			return (NULL);
		}
	}
	if (access(tokens[0], X_OK) == 0)
	{
		path = tokens[0];
		return (path);
	}
	else if (access(tokens[0], X_OK) != 0)
	{
		pathLL = path_list();
		path = finding_executable(tokens[0], pathLL);

		if (path == NULL)
		{
			perror(Str_cat(tokens[0], ": command not found\n"));
		}
		else
		{
			return (path);
		}
	}
	return (NULL);
}

/**
 * execute - creates a child process using fork() and executes command
 * @tokens: commands executed
 */

void execute(char **tokens)
{
	pid_t pid;
	int status;
	char *path = command_checker(tokens);

	if (path == NULL)
	{
		return;
	}
	else if (strcmp(path, "error") == 0) /*check for error code*/
	{
		write(STDERR_FILENO, "Invalid command\n", strlen("Invalid command\n"));
		return;
	}

	pid = fork(); /* create child process using fork before calling execve()*/
	if (pid == 0) /* if pid == 0 execute child process */
	{
		if (execve(path, tokens, environ) == -1) /*check for errors*/
		{
			perror("execve failure"); /*handle error*/
			exit(1);
		}
	}
	else if (pid > 0) /* fork() is > 0 for parent process thus pid > 0 */
	{
		if (waitpid(pid, &status, 0) == -1) /*check for errors*/
		{
			perror("waitpid failed"); /*print error msg*/
			exit(1);
		}
		/*it's parent process, ask it to wait for child process to complete*/
	}
	else /* only true if fork() fails pid == -1 */
	{
		perror("fork failed");
		exit(1);
	}
}
