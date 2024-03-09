#include "shell.h"
/**
 * free_list - frees linked list
 * @head: a pointer to the head node of the list
 */
void free_list(LL *head)
{
	LL *temp;

	while (head != NULL)
	{
		temp = head; /* store current head */
		head = head->next; /* move to next node */
		free(temp->str); /* free string */
		free(temp); /* free node */
	}
}
/**
 * add_node - adds a new node to the list
 * @head_ref: a double pointer to the head node
 * @str: string stored on the new node
 */
void add_node(LL **head_ref, char *str)
{
	LL *new_node = (LL *)malloc(sizeof(LL)); /* allocate memory for new node */

	new_node->str = str; /* assign string to new node */
	new_node->next = *head_ref; /* make the new node point to the current head */
	*head_ref = new_node; /* make the new node the new head */
}
/**
 * path_list - finds the path in env variable
 * Return: head node to the linked list
 */
LL *path_list(void)
{
	LL *head = NULL;
	char *path = getenv("PATH");
	char *path_copy = strd_up(path);
	LL *node;
	char *token;

	if (!path_copy)
	{
		perror("malloc failure");
		return (NULL);
	}
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		node = malloc(sizeof(LL));
		if (!node)
		{
			perror("malloc failure");
			free_list(head);
			free(path_copy);
			return (NULL);
		}

		node->str = strd_up(token);
		node->next = head;
		head = node;

		token = strtok(NULL, ":");
	}
	free(path_copy);

	return (head);
}
/**
 * finding_executable - checks if the file exists and is executable
 * @command: command being executed
 * @path_list: list of directories to check command
 * Return: executable path for the command
 */
char *finding_executable(char *command, LL *path_list)
{
	char *executable_path = NULL;
	char *path = NULL;
	int command_len = StringLength(command);
	int path_len;
	int new_len;
	char *new_path;

	while (path_list != NULL)
	{
		path = path_list->str;
		path_len = StringLength(path);
		new_len = path_len + command_len + 2;
		new_path = malloc(new_len * sizeof(char));
		if (new_path == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		Str_cpy(new_path, path);
		Str_cat(new_path, "/");
		Str_cat(new_path, command);
		if (access(new_path, X_OK) == 0)
		{
			executable_path = new_path;
		break;
		}
		free(new_path);
		path_list = path_list->next;
	}
	return (executable_path);
}
/**
 * get_env - gets the value stored in specified variable name
 * @name: Variable name
 * Return: values in the variable
 */
char *get_env(const char *name)
{
	int i, len; /* i is used to traverse environ global variable */
	char *env_val; /* string to store value of variable name e.g PATH="env_val" */

	len = StringLength(name); /* length of variable name e.g ("PATH" = 4)*/

	for (i = 0; environ[i] != NULL; i++)
	{
		if (Strn_cmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			env_val = &environ[i][len + 1];
			return (env_val);
		}
	}

	return (NULL);
}
