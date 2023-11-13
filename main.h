#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>

/**
 * struct s_cmd - represents a command
 *
 * @cmd: command to be exectued
 *
 * @args: array of arguments for the command
 *
 * @env: enviroment variables
 *
 * @out_files: output files
 */

typedef struct s_cmd
{
	char *cmd;
	char **args;
	char **env;
	char **out_files;
} t_cmd;

/**
 * struct s_garbage - garbage linked list item
 *
 * @ptr: pointer to the allocated memory to be cleaned
 *
 * @next: pointer to the next item in the list
 */

typedef struct s_garbage
{
	void *ptr;
	struct s_garbage *next;
} t_garbage;

char *_strncpy(char *dest, const char *src, int n);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, unsigned int n);
int _strlen(char const *str);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
size_t _strcspn(char *str, char *str2);
void add_back_garbage(t_garbage **head, void *data);
t_cmd *init_cmd(void);
void clear_garbage(t_garbage **head);
char **ft_split_spaces(char const *s);
char **ft_split(char const *s, char c);
char *_getenv(char **env);
bool _builtin(char *cmd);
void _execute_builtin(char **cmd, char **env);

#endif
