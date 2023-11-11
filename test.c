# include <libc.h>

int main(int c, char **v, char **env)
{
	if (execve("/bin/ls", v, env) == -1)
		printf("Error: execve failed\n");
}