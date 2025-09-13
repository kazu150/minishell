#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc main.c -lreadline -o main
int	main(void)
{
	char *line = NULL;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		printf("line is %s\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}