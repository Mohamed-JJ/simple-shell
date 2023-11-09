#ifndef MAIN_H
#define MAIN_H

# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>


typedef struct s_cmd
{
        char    *cmd;
        char    **args;
        char    **env;
        char    **out_files;
}                               t_cmd;


typedef struct s_garbage
{
        void    *ptr;
        struct s_garbage        *next;
}				t_garbage;

char *_strncpy(char *dest, const char *src, int n);
int _strcmp(char *s1, char *s2);
int _strlen(char const *str);
char *_strdup(char *str);
size_t _strcspn(char *str , char *str2);

#endif
