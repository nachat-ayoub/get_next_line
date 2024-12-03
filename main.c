#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
// #include "get_next_line_bonus.h"

int main()
{
	// int fd = open("test.txt", O_WRONLY | O_CREAT, 0777);
	int fd = open("test.txt", O_RDONLY);
	char *line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		printf("==> Line: '%s'\n", line);
		if(line == NULL)
			break ;
	}
}