#include "shell.h"

/**
 * handle_semicolon - handles ";" separation
 * @input: input string to be tokenized
 */
void handle_semicolon(char *input)
{
	char *commands[MAX_ARGS];
	char *args[MAX_ARGS];
	pid_t pid;
	int j, status;

	delim_token(input, commands, MAX_NUM_TOKENS, ";");

	for (j = 0; commands[j] != NULL; j++)
	{
		delim_token(commands[j], args, MAX_NUM_TOKENS, " \t\n");
		if (args[0] != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execute(args);
				exit(0);
			}
			else if (pid < 0)
			{
				perror("fork failed");
				exit(1);
			}
			else
			{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			}
		}
	}
}

/**
 * delim_token - breaks a string into tokens with strtok()
 * @input: input string that needs to be tokenized.
 * @tokens: array that will hold the resulting tokens
 * @max_tokens: max no of tokens that can be extracted from the input string
 * @delim: delimiter string
 * Return: number of tokens
 */
int delim_token(char *input, char **tokens, int max_tokens, char *delim)
{
	int num_tokens = 0;
	char *token = strtok(input, delim);

	while (token != NULL && num_tokens < max_tokens)
	{
		tokens[num_tokens] = token;
		num_tokens++;
		token = strtok(NULL, delim);
	}
	tokens[num_tokens] = NULL;
	return (num_tokens);
}
