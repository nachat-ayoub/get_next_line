#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


void f()
{
	system("leaks a.out");
}
int main()
{
	// atexit(f);
	// char  str[1024];
	int fd = open("test.txt", O_RDONLY);
	char *line = NULL;

	while (1)
	{
		line = get_next_line(fd);
		printf(GREEN "Line: '%s'\n" RESET, line);
		if(line == NULL)
			break ;
	}
	// free(line1);
}